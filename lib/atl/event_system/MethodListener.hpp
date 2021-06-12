#pragma once
//atl
#include <atl/event_system/Listener.hpp> //event_system::IListener
#include <atl/util/Shared.hpp> //util::Shared

namespace atl::event_system {
	template <class TObject, class ...TParams>
	class MethodListener : public IListener <TParams...> {
	public:
		using TMethod = void(TObject::*)(TParams...);

		MethodListener(TObject& _object, TMethod _method) : 
		IListener <TParams...>(), m_object(_object), m_method(_method) {
			if (m_method == nullptr)
				throw "MethodListnener: _method must be not nullptr!";
		}
		~MethodListener() {}

		void call(TParams... _params) final override {
			return (m_object.*m_method)(_params...);
		}
		bool equals(const IListener <TParams...>& _another) const final override {
			const MethodListener* upcasted = dynamic_cast <const MethodListener*>(&_another);
			return m_object == upcasted->m_object && m_method == upcasted->m_method;
		}

	protected:
		TObject& m_object;
		TMethod m_method;
	};
}