#pragma once
//atl
#include <atl/event_system/Listener.hpp> //event_system::IListener

namespace atl::event_system {
	template <class TObject, class ...TParams>
	class MethodListener : public IListener <TParams...> {
	public:
		using TMethod = void(TObject::*)(TParams...);

		MethodListener(TObject& object, TMethod method) : 
		IListener <TParams...>(), m_object(object), m_method(method) {
			if (m_method == nullptr)
				throw "MethodListnener: method must be not nullptr!";
		}
		~MethodListener() {}

		void call(TParams... params) final override {
			return (m_object.*m_method)(params...);
		}
		bool equals(const IListener <TParams...>& listener) const final override {
			const MethodListener* another = dynamic_cast <const MethodListener*>(&listener);
			return m_object == another->m_object && m_method == another->m_method;
		}

	protected:
		TObject& m_object;
		TMethod m_method;
	};
}