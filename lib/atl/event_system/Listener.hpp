#pragma once
//atl
#include <atl/util/Shared.hpp> //util::Shared

namespace atl::event_system {
	template <class ...TParams>
	class IListener {
	protected:
		IListener() {}

	public:
		virtual void call(TParams... params) = 0;

		virtual bool equals(const IListener&) const = 0;
	};

	template <class ...TParams>
	using Listener = util::Shared <IListener <TParams...>>;
}