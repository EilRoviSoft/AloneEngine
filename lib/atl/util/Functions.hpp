#pragma once
//std
#include <iostream> //istream, ostream
#include <cstdlib> //rand
#include <string> //string

//uxl
#include <uxl/basic_types.hpp> //uint64
#include <uxl/hash.hpp> //hash (for string)

namespace atl {
	using cstring = char*;

	//end > start
	size_t random(size_t start, size_t end) {
		auto delta = end - start;
		return rand() % delta + start;
	}
	
	//if using for strings, use hash(cstirng, size_t) instead
	template <class Type>
	constexpr size_t hash(Type what) {
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