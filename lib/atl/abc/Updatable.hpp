#pragma once
//std
#include <concepts> //std::derived_from

//sf
#include <SFML/System/Clock.hpp> //Clock

namespace atl {
	//TODO: change clock type
	class IUpdatable {
	public:
		virtual void update(size_t dt) = 0;
	};

	template <class Type>
	class IPostable {
		template <class Type>
		friend class IReceivable;
	public:
		virtual Type post() const = 0;
	};

	template <class Type>
	class IReceivable {
	public:
		virtual void receive(const IPostable <Type>& what) = 0;
	};
}