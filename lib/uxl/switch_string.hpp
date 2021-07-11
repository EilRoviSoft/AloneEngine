#pragma once
//uxl
#include <uxl/basic_types.hpp> //uint64
#include <uxl/hash.hpp> //hash (for strings)

namespace uxl {
	constexpr size_t getStringLength(const char* what) {
		return *what ? (1 + getStringLength(what + 1)) : 0;
	}

	constexpr size_t isStringCorrect(const char* what) {
		return ((int8) *what > 0) ? isStringCorrect(what + 1) : (*what ? false : true);
	}
}

//idk what's better: have collisions and bigger size or not...

#define case_str(what) static_assert(uxl::isStringCorrect(what), "case_str input contains wrong characters!");\
case uxl::hash(what, uxl::getStringLength(what))

#define switch_str(what) switch(uxl::hash(what, uxl::getStringLength(what)))