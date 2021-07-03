#pragma once
//std
#include <vector> //vector
#include <istream> //istream

//atl
#include <atl/abc/Loadable.hpp> //abc::ILoadable

namespace atl::abc {
	/*template <class Type>
	using FlatIterator = std::vector <Type>::iterator;

	template <class Type, class UnitType>
	class FlatLoadable : public ILoadable <std::pair <FlatIterator <Type>, FlatIterator <Type>>> {
	public:
		bool loadFromStream(std::istream& in) final override {
			size_t count;
			UnitType temp;
			std::vector <Type> result;

			in >> count;
			result.resize(count);

			for (size_t i = 0; i != count; i++) {
				in >> temp;
				result.at(i) = Type(temp);
			}

			return load(std::make_pair(result.begin(), result.end()));
		}
	};*/
}