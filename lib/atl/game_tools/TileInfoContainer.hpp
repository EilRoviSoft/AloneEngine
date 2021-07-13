#pragma once
//sf
#include <SFML/Graphics/Texture.hpp> //Texture

//std
#include <map> //map

//atl
#include <atl/abc/XmlLoadable.hpp> //XmlLoadable, pugi::xml_node
#include <atl/game_tools/Tile.hpp> //TileInfo
#include <atl/game_tools/TileInfoFactory.hpp> //Factory

namespace atl {
	class TileInfoContainer : public XmlLoadable {
	public:
		TileInfo& operator[](size_t id);
		const TileInfo& operator[](size_t id) const;

		virtual bool load(const pugi::xml_node& data) override;

	private:
		std::map <size_t, TileInfo> _content;
	};
}