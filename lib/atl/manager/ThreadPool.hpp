#pragma once
//std
#include <vector> //vector
#include <thread> //jthread, this_thread::sleep
#include <atomic> //atomic
#include <functional> //function, bind
#include <mutex> //mutex
#include <condition_variable> //condition_variable
#include <future> //future, packaged_task
#include <type_traits> //forward
#include <memory> //unique_ptr, shared_ptr
#include <chrono> //chrono::miliseconds
#include <iostream> //std::cerr

//atl
#include <atl/thread_safe/Queue.hpp> //thread_safe::Queue

namespace atl::manager {
	using Task = std::function <void()>;

	//Based on vit-vit/ctpl
	class ThreadPool {
	public:
		ThreadPool(size_t _count = std::thread::hardware_concurrency()) {
			resize(_count);
		}
		~ThreadPool() {}

		void start() {
			for (auto& it : m_workers)
				if (it.joinable()) it.detach();
		}
		//may take a lot of time, because of waiting the end of execution tasks
		void stop(size_t _timeout = 500, bool _isWait = false) {
			if (!_isWait) {
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
				m_cv.notify_all();
			}

			while (m_aliveThreads != 0)
				std::this_thread::sleep_for(std::chrono::milliseconds(_timeout));
		}

		size_t size() const {
			return m_workers.size();
		}
		size_t idle() const {
			return m_idleThreads;
		}

		std::thread& get(size_t _number) {
			return m_workers.at(_number);
		}

		void resize(size_t _countNow) {
			m_aliveThreads = _countNow;

			size_t countBefore = m_workers.size();
			if (_countNow == countBefore)
				return;

			if (!m_isStop && !m_isDone) {
				if (countBefore < _countNow) {
					m_workers.resize(_countNow);
					m_flags.resize(_countNow);

					for (size_t i = countBefore; i != _countNow; i++) {
						m_flags.at(i) = std::shared_ptr <std::atomic <bool>>(new std::atomic <bool>(false));
						_set_thread(i);
					}
				} else {
					for (size_t i = countBefore - 1; i != _countNow; i++) {
						*m_flags.at(i) = true;
						m_workers[i].detach();
					}
					{
						std::unique_lock lock(m_mutex);
						m_cv.notify_all();
					}

					m_workers.resize(_countNow);
					m_flags.resize(_countNow);
				}
			}
		}

		template <class ReturnType, class... TParams>
		std::future <ReturnType> request(std::function <ReturnType(TParams...)> _function, TParams... _args) {
			auto pckg = std::shared_ptr <std::packaged_task <ReturnType()>>(
				new std::packaged_task <ReturnType()>(std::bind(_function, _args...)));
			m_requests.push(Task([pckg]() {
				(*pckg)();
			}));

			std::unique_lock lock(m_mutex);
			m_cv.notify_one();

			return pckg->get_future();
		}

	protected:
		std::vector <std::thread> m_workers;
		std::vector <std::shared_ptr <std::atomic <bool>>> m_flags;
		thread_safe::Queue <Task> m_requests;

		std::atomic <bool> m_isDone = false, m_isStop = false;
		std::atomic <size_t> m_idleThreads = 0, m_aliveThreads = 0;

		std::mutex m_mutex;
		std::condition_variable m_cv;

	private:
		void _set_thread(size_t _id) {
			m_workers.at(_id) = std::thread(&ThreadPool::_thread_algorythm, std::ref(*this), _id);
		}

		void _thread_algorythm(size_t _id) {
			std::atomic <bool>& flag = *m_flags.at(_id);
			auto function = std::move(m_requests.try_pop());

			while (true) {
				while (function.get() != nullptr) {
					try {
						(*function)();
					} catch (std::exception _e) {
						std::cerr << _e.what();
					}

					function.reset(nullptr);

					if (flag)
						return;
					else {
						function = std::move(m_requests.try_pop());
					}
				}

				std::unique_lock lock(m_mutex);
				m_idleThreads++;
				m_cv.wait(lock, [this, &flag, &function]() {
					function = std::move(m_requests.try_pop());
					return (function.get() != nullptr) || m_isDone || flag;
				});
				m_idleThreads--;

				if (function.get() == nullptr) {
					m_aliveThreads--;
					return;
				}
			}
		}
	};
}