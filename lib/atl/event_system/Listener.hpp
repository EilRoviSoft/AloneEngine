#pragma once
//std
#include <memory> //shared_ptr

namespace atl::event_system {
	template <class ...TParams>
	class IListener {
	protected:
		IListener() {}

	public:
		virtual void call(TParams... params) = 0;

		virtual bool equals(const IListener& listener) const = 0;
	};

	template <class ...TParams>
	using Listener = std::shared_ptr <IListener <TParams...>>;
}