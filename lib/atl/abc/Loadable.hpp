#pragma once
//std
#include <string> //string
#include <fstream> //ifstream, istream

namespace atl::abc {
	template <class UserDataType>
	class ILoadable {
	public:
		using Type = UserDataType;

		virtual bool loadFromFile(const std::string& filename) {
			std::ifstream file(filename);
			auto result = loadFromStream(file);
			file.close();

			return result;
		}
		virtual bool loadFromStream(std::istream& in) = 0;
		//You have to override it yourself
		virtual bool load(const UserDataType& data) = 0;
	};
}