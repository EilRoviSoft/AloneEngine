#pragma once
//std
#include <vector> //vector
#include <thread> //thread, this_thread::sleep
#include <atomic> //atomic
#include <functional> //function, bind
#include <mutex> //mutex
#include <condition_variable> //condition_variable
#include <future> //future, packaged_task
#include <type_traits> //forward
#include <memory> //unique_ptr, shared_ptr
#include <chrono> //chrono::miliseconds
#include <iostream> //cerr

//atl
#include <atl/thread_safe/Queue.hpp> //thread_safe::Queue

namespace atl {
	using Task = std::function <void()>;

	//Based on vit-vit/ctpl
	class ThreadPool {
	public:
		ThreadPool(size_t count = std::thread::hardware_concurrency());
		~ThreadPool();

		void start();
		//may take a lot of time, because of waiting the end of execution tasks
		void stop(size_t timeout = 500, bool isWait = false);

		size_t size() const;
		size_t idle() const;

		std::thread& get(size_t number);

		void resize(size_t countNow);

		template <class ReturnType, class... TParams>
		std::future <ReturnType> request(std::function <ReturnType(TParams...)> function, TParams... args);

	protected:
		std::vector <std::thread> m_workers;
		std::vector <std::shared_ptr <std::atomic <bool>>> m_flags;
		thread_safe::Queue <Task> m_requests;

		std::atomic <bool> m_isDone = false, m_isStop = false;
		std::atomic <size_t> m_idleThreads = 0, m_aliveThreads = 0;

		std::mutex m_mutex;
		std::condition_variable m_condition;

	private:
		void _set_thread(size_t id);

		void _thread_algorythm(size_t id);
	};
}