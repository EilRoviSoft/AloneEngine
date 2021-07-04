#pragma once
//atl
#include <atl/event_system/Publisher.hpp> //IPublisher

namespace atl {
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