#pragma once
//std
#include <fstream> //ifstream, istream

//nlohmann (json)
#include <nlohmann/json.hpp> //json

//atl
#include <atl/abc/Loadable.hpp> //ILoadable

namespace atl {
	class JsonLoadable : public ILoadable <const nlohmann::json&> {
	public:
		bool loadFromStream(std::istream& in) override final {
			return load(nlohmann::json::parse(in));
		}
	};
}