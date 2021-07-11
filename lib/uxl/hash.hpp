#pragma once
//std
#include <climits> //ULLONG_MAX

//uxl
#include <uxl/basic_types.hpp> //uint64, cstring

namespace uxl {
	constexpr uint64 hash(const char* str, size_t length) {
		const uint64 Bits = (uint64) (sizeof(uint64) * 8);
		const uint64 ThreeQuarters = (uint64) (Bits * 3 / 4);
		const uint64 OneEight = (uint64) (Bits / 8);
		const uint64 HighBits = (uint64) (ULLONG_MAX) << (Bits - OneEight);

		uint64 result = 0, temp = 0;

		for (size_t i = 0; i != length; i++, str++) {
			result = (result << OneEight) + (*str);

			if ((temp = result & HighBits) != 0)
				result = ((result ^ (temp >> ThreeQuarters)) & (~HighBits));
		}

		return result;
	}
}