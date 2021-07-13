#include "TileInfoFactory.hpp"

//atl
#include <atl/game_tools/Core.hpp> //context

//TileInfoFactory
atl::TileInfo atl::TileInfoFactory::create(const pugi::xml_node& data, const std::string& texture_name) {
	std::string type = data.name();
	const auto& texture = context.textures.at(texture_name);
	auto result = TileInfo(nullptr);

	if (type == "ITileInfo") {
		result.reset(new ITileInfo(texture));
		result->load(data);
	}

	return result;
}