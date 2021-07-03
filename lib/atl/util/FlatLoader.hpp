#pragma once
//std
#include <vector> //vector
#include <istream> //istream

namespace atl::util {
	struct FlatLoader {
		template <class UnitType, class ResultType>
		static std::vector <ResultType> load(std::istream& in) {
			size_t size;
			UnitType temp;
			in >> size;

			std::vector <ResultType> result;
			result.resize(size);

			for (size_t i = 0; i != result.size(); i++) {
				in >> temp;
				result.at(i) = temp;
			}

			return result;
		}
	};
}