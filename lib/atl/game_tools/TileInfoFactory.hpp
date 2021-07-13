#pragma once
//std
#include <string> //string

//pugi
#include <pugixml/pugixml.hpp> //xml_node

//atl
#include <atl/game_tools/Tile.hpp> //TileInfo

namespace atl {
	struct TileInfoFactory {
		static TileInfo create(const pugi::xml_node& data, const std::string& texture_name);
	};
}