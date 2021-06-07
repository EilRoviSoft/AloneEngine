#pragma once
#include <thread> //thread

namespace atl::abc {
	class IRunnable {
	protected:
		std::thread m_thread;
		virtual void run() = 0;

	public:
		IRunnable() : m_thread(&IRunnable::run, this) {}

		void join() {
			return this->m_thread.join();
		}
		void detach() {
			return this->m_thread.detach();
		}

		size_t id() const {
			return std::hash <std::thread::id> {}(this->m_thread.get_id());
		}
	};
}