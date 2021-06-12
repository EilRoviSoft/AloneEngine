#pragma once
//atl
#include <atl/event_system/Publisher.hpp> //event_system::IPublisher

namespace atl::event_system {
	template <class ...TParams>
	class IEvent : protected IPublisher <TParams...> {
	public:
		IEvent() : IPublisher <TParams...>() {}
		~IEvent() {}

		void operator()(TParams ..._params) {
			return invoke(_params...);
		}

		bool operator+=(Listener <TParams...>& _listener) {
			return subscribe(_listener);
		}
		bool operator-=(Listener <TParams...>& _listener) {
			return unsubscribe(_listener);
		}
	};
}