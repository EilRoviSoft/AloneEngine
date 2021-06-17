#pragma once
//std
#include <cstdint> //int32_t

namespace atl::util {
	template <class Type>
	size_t hash(Type _what) {
		return std::hash <Type> {}(_what);
	}
}