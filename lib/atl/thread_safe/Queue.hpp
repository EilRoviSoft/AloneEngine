#pragma once
//std
#include <list> //list
#include <queue> //queue
#include <initializer_list> //initializer_list
#include <mutex> //m_mutex
#include <memory> //unique_ptr, make_unique

namespace atl::thread_safe {
	template <class Type>
	class Queue {
	protected:
		std::queue <Type, std::list <Type>> m_storage;
		std::mutex m_lock;

	public:
		Queue() {}
		Queue(std::initializer_list <Type>& _init) {
			for (const auto& it : _init)
				m_storage.push(it);
		}

		//data access

		//can cause exception
		Type front() {
			std::lock_guard lock(m_lock);
			return m_storage.front();
		}
		//can cause exception
		Type back() {
			std::lock_guard lock(m_lock);
			return m_storage.back();
		}

		//modifying

		void push(Type&& _what) {
			std::lock_guard lock(m_lock);
			m_storage.push(_what);
		}
		void push(const Type& _what) {
			m_storage.push(_what);
		}
		//can cause exception
		Type pop() {
			std::lock_guard lock(m_lock);

			Type result = m_storage.front();
			m_storage.pop();

			return result;
		}
		std::unique_ptr <Type> try_pop() {
			std::lock_guard lock(m_lock);
			if (m_storage.empty()) return std::unique_ptr <Type>(nullptr);

			Type* result = new Type(m_storage.front());
			m_storage.pop();

			return std::unique_ptr <Type>(result);
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