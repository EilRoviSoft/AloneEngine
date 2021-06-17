#pragma once
//atl
#include <atl/event_system/Publisher.hpp> //event_system::IPublisher

namespace atl::event_system {
	template <class ...TParams>
	class IEvent : protected IPublisher <TParams...> {
	public:
		IEvent() : IPublisher <TParams...>() {}
		~IEvent() {}

		void operator()(TParams ...params) {
			return invoke(params...);
		}

		bool operator+=(Listener <TParams...>& listener) {
			return subscribe(listener);
		}
		bool operator-=(Listener <TParams...>& listener) {
			return unsubscribe(listener);
		}
	};
}