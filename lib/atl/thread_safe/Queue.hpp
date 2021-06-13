#pragma once
//std
#include <list> //list
#include <queue> //queue
#include <initializer_list> //initializer_list
#include <mutex> //m_mutex
#include <memory> //unique_ptr, make_unique

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

		//can cause exception
		T front() {
			std::lock_guard lock(m_lock);
			return m_storage.front();
		}
		//can cause exception
		T back() {
			std::lock_guard lock(m_lock);
			return m_storage.back();
		}

		//modifying

		void push(T&& _what) {
			std::lock_guard lock(m_lock);
			m_storage.push(_what);
		}
		void push(const T& _what) {
			m_storage.push(_what);
		}
		//can cause exception
		T pop() {
			std::lock_guard lock(m_lock);

			T result = m_storage.front();
			m_storage.pop();

			return result;
		}
		std::unique_ptr <T> try_pop() {
			std::lock_guard lock(m_lock);
			if (m_storage.empty()) return std::unique_ptr <T>(nullptr);

			T* result = new T(m_storage.front());
			m_storage.pop();

			return std::unique_ptr <T>(result);
		}
		void clear() {
			m_storage.clear();
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