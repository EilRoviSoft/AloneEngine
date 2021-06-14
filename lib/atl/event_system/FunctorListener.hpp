#pragma once
//std
#include <concepts> //std::invocable
#include <memory> //std::shared_ptr

//atl
#include <atl/event_system/Listener.hpp> //event_system::IListener

namespace atl::event_system {
	template <class TInvocable, class ...TParams>
	requires std::invocable <TInvocable>
	class FunctorListener : IListener <TParams...> {
	public:
		FunctorListener(TInvocable& _invocable) : 
		IListener <TParams...>(), m_invocable(_invocable) {}

		void call(TParams... _params) final override {
			return m_invocable(_params);
		}

		bool equals(const IListener <TParams...>& _another) const final override {
			const FunctorListener* upcasted = dynamic_cast <const FunctorListener*>(&_another);
			return m_invocable == upcasted->m_invocable;
		}

	protected:
		TInvocable& m_invocable;
	};
}