#pragma once
//std
#include <list> //list
#include <shared_mutex> //shared_mutex

//atl
#include <atl/event_system/Listener.hpp> //event_system::IListener

namespace atl::event_system {
	template <class ...TParams>
	class IPublisher {
		using ListenerIt = std::list <Listener <TParams...>>::const_iterator;

	public:
		IPublisher() : m_listeners(), m_lock() {}
		~IPublisher() {}

		void invoke(TParams ..._params) {
			m_lock.lock_shared();

			for (auto it : m_listeners) {
				m_lock.unlock_shared();
				it->call(_params...);
				m_lock.lock_shared();
			}

			m_lock.unlock_shared();
		}

		bool subscribe(Listener <TParams...>& _listener) {
			std::unique_lock lock(m_lock);

			if (_find(_listener) != m_listeners.cend())
				return false;

			m_listeners.push_back(_listener);
			return true;
		}
		bool unsubscribe(Listener <TParams...>& _listener) {
			std::unique_lock lock(m_lock);

			auto iter = _find(_listener);
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
		ListenerIt _find(const Listener <TParams...>& _what) const {
			return std::find_if(m_listeners.cbegin(), m_listeners.cend(), [&_what](const Listener <TParams...>& _temp) {
				return _temp->equals(*_what);
			});
		}
	};
}