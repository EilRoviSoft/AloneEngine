#pragma once
//std
#include <iostream> //istream, ostream

namespace atl {
	template <class Type>
	size_t hash(Type what) {
		return std::hash <Type> {}(what);
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