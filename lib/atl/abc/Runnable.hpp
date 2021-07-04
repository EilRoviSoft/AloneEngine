#pragma once
//std
#include <thread> //thread

//atl
#include <atl/util/Functions.hpp> //hash

namespace atl {
	class IRunnable {
	public:
		IRunnable() : m_thread(&IRunnable::run, this) {}

		void join() {
			return this->m_thread.join();
		}
		void detach() {
			return this->m_thread.detach();
		}

		size_t getId() const {
			return hash(this->m_thread.get_id());
		}

	protected:
		std::thread m_thread;
		virtual void run() = 0;
	};
}