#include "ThreadPool.hpp"

atl::ThreadPool::ThreadPool(size_t count) {
	resize(count);
}
atl::ThreadPool::~ThreadPool() {}

void atl::ThreadPool::start() {
	for (auto& it : m_workers)
		if (it.joinable()) it.detach();
}
void atl::ThreadPool::stop(size_t timeout, bool isWait) {
	if (!isWait) {
		if (m_isStop)
			return;

		m_isStop = true;
		for (size_t i = 0, count = m_workers.size(); i != count; i++)
			*m_flags.at(i) = true;
	} else {
		if (m_isDone || m_isStop)
			return;

		m_isDone = true;
	}
	{
		std::unique_lock lock(m_mutex);
		m_condition.notify_all();
	}

	while (m_aliveThreads != 0)
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
}

size_t atl::ThreadPool::size() const {
	return m_workers.size();
}
size_t atl::ThreadPool::idle() const {
	return m_idleThreads;
}

std::thread& atl::ThreadPool::get(size_t number) {
	return m_workers.at(number);
}

void atl::ThreadPool::resize(size_t countNow) {
	m_aliveThreads = countNow;

	size_t countBefore = m_workers.size();
	if (countNow == countBefore)
		return;

	if (!m_isStop && !m_isDone) {
		if (countBefore < countNow) {
			m_workers.resize(countNow);
			m_flags.resize(countNow);

			for (size_t i = countBefore; i != countNow; i++) {
				m_flags.at(i) = std::shared_ptr <std::atomic <bool>>(new std::atomic <bool>(false));
				_set_thread(i);
			}
		} else {
			for (size_t i = countBefore - 1; i != countNow; i++) {
				*m_flags.at(i) = true;
				m_workers[i].detach();
			}
			{
				std::unique_lock lock(m_mutex);
				m_condition.notify_all();
			}

			m_workers.resize(countNow);
			m_flags.resize(countNow);
		}
	}
}

template<class ReturnType, class ...TParams>
std::future<ReturnType> atl::ThreadPool::request(std::function<ReturnType(TParams...)> function, TParams ...args) {
	auto pckg = std::shared_ptr <std::packaged_task <ReturnType()>>(
		new std::packaged_task <ReturnType()>(std::bind(function, args...)));
	m_requests.push(Task([pckg]() {
		(*pckg)();
	}));

	std::unique_lock lock(m_mutex);
	m_condition.notify_one();

	return pckg->get_future();
}

void atl::ThreadPool::_set_thread(size_t id) {
	m_workers.at(id) = std::thread(&ThreadPool::_thread_algorythm, std::ref(*this), id);
}

void atl::ThreadPool::_thread_algorythm(size_t id) {
	std::atomic <bool>& flag = *m_flags.at(id);
	auto function = std::move(m_requests.try_pop());

	while (true) {
		while (function.get() != nullptr) {
			try {
				(*function)();
			} catch (std::exception e) {
				std::cerr << e.what();
			}

			function.reset(nullptr);

			if (flag)
				return void();
			else {
				function = std::move(m_requests.try_pop());
			}
		}

		std::unique_lock lock(m_mutex);
		m_idleThreads++;
		m_condition.wait(lock, [this, &flag, &function]() {
			function = std::move(m_requests.try_pop());
			return (function.get() != nullptr) || m_isDone || flag;
		});
		m_idleThreads--;

		if (function.get() == nullptr) {
			m_aliveThreads--;
			return void();
		}
	}
}