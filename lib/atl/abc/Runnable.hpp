#pragma once
//std
#include <thread> //thread

//atl
#include <atl/util/Functions.hpp> //util::hash

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
			return util::hash(this->m_thread.get_id());
		}
	};
}