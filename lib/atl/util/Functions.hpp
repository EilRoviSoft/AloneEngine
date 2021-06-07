#pragma once
namespace atl::util {
	template <class Type>
	size_t hash(Type _what) {
		return std::hash <Type> {}(_what);
	}
}