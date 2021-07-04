#pragma once
//std
#include <list> //list
#include <shared_mutex> //shared_mutex

//atl
#include <atl/event_system/Listener.hpp> //IListener

namespace atl {
	template <class ...TParams>
	class IPublisher {
		using ListenerIt = std::list <Listener <TParams...>>::const_iterator;
	public:
		IPublisher() : m_listeners(), m_lock() {}
		~IPublisher() {}

		void invoke(TParams ...params) {
			m_lock.lock_shared();

			for (auto it : m_listeners) {
				m_lock.unlock_shared();
				it->call(params...);
				m_lock.lock_shared();
			}

			m_lock.unlock_shared();
		}

		bool subscribe(Listener <TParams...>& listener) {
			std::unique_lock lock(m_lock);

			if (_find(listener) != m_listeners.cend())
				return false;

			m_listeners.push_back(listener);
			return true;
		}
		bool unsubscribe(Listener <TParams...>& listener) {
			std::unique_lock lock(m_lock);

			auto iter = _find(listener);
			if (iter == m_listeners.cend())
				return false;

			m_listeners.erase(iter);
			return true;
		}

	protected:
		std::list <Listener <TParams...>> m_listeners;
		std::shared_mutex m_lock;

	private:
		//requires shared locking
		ListenerIt _find(const Listener <TParams...>& what) const {
			return std::find_if(m_listeners.cbegin(), m_listeners.cend(), [&what](const Listener <TParams...>& temp) {
				return temp->equals(*what);
			});
		}
	};
}