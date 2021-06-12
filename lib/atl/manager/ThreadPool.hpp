#pragma once
//std
#include <functional> //function, bind
#include <list> //list
#include <thread> //thread
#include <shared_mutex> //shared_mutex

//atl
#include <atl/thread_safe/Queue.hpp> //Queue

namespace atl::manager {
	class ThreadPool {
	protected:
		thread_safe::Queue <std::function <void()>> m_listeners;

	public:
		ThreadPool() {}
	};
}