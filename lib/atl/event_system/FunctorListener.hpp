#pragma once
//std
#include <concepts> //invocable
#include <memory> //shared_ptr

//atl
#include <atl/event_system/Listener.hpp> //IListener

namespace atl {
	template <class TInvocable, class ...TParams>
	requires std::invocable <TInvocable>
	class FunctorListener : public IListener <TParams...> {
	public:
		FunctorListener(TInvocable& invocable) : 
		IListener <TParams...>(), m_invocable(invocable) {}

		void call(TParams... params) final override {
			return m_invocable(params);
		}

		bool equals(const IListener <TParams...>& listener) const final override {
			const FunctorListener* another = dynamic_cast <const FunctorListener*>(&listener);
			return m_invocable == another->m_invocable;
		}

	protected:
		TInvocable& m_invocable;
	};
}