#pragma once
//std
#include <iostream> //istream, ostream

namespace atl::util {
	template <class Type>
	size_t hash(Type _what) {
		return std::hash <Type> {}(_what);
	}

	template <class Type>
	Type scan(std::istream& from = std::cin) {
		Type to;
		from >> to;
		return to;
	}

	template <class Type>
	void print(const Type& what, std::ostream& to = std::cout) {
		to << what;
	}
}