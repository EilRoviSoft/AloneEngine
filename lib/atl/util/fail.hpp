#pragma once
//std
#include <type_traits> //false_type

namespace atl::util {
	template <class Type>
	struct fail : public std::false_type {};
}