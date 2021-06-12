#pragma once
//std
#include <list> //list
#include <queue> //queue
#include <initializer_list> //initializer_list
#include <mutex> //mutex

namespace atl::thread_safe {
	template <class T>
	class Queue {
	protected:
		std::queue <T, std::list <T>> m_storage;
		std::mutex m_lock;

	public:
		Queue() {}
		Queue(std::initializer_list <T>& _init) {
			for (const auto& it : _init)
				m_storage.push(it);
		}

		//data access
		T front() {
			std::lock_guard lock(m_lock);
			return m_storage.front();
		}
		T back() {
			std::lock_guard lock(m_lock);
			return m_storage.back();
		}

		//modifying
		void push(T&& _what) {
			std::lock_guard lock(m_lock);
			m_storage.push(_what);
		}
		T pop() {
			std::lock_guard lock(m_lock);
			T result = m_storage.front();
			m_storage.pop();
			return result;
		}

		//size
		bool empty() {
			std::lock_guard lock(m_lock);
			return m_storage.empty();
		}
		size_t size() {
			std::lock_guard lock(m_lock);
			return m_storage.size();
		}
	};
}