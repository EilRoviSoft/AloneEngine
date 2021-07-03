#pragma once
//std
#include <fstream> //ifstream, istream, ios_base

//toml
#include <toml/include.hpp> //value

//atl
#include <atl/abc/Loadable.hpp> //abc::ILoadable

namespace atl::abc {
	class TomlLoadable : public ILoadable <const toml::value&> {
	public:
		//it's crutch, because of Windows weird reading toml file
		bool loadFromFile(const std::string& filename) override final {
			std::ifstream file(filename, std::ios_base::binary);
			auto result = loadFromStream(file);
			file.close();

			return result;
		}
		bool loadFromStream(std::istream& in) override final {
			return load(toml::parse(in));
		}
	};
}