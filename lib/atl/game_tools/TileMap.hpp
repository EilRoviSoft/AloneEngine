#pragma once
//sf
#include <SFML/Graphics.hpp> //Drawable, Sprite, RenderTarget, RenderStates

//std
#include <cstdint> //uint8_t
#include <memory> //shared_ptr
#include <map> //map
#include <string> //string

//atl
#include <atl/abc/XmlLoadable.hpp> //XmlLoadable, pugi::xml_node
#include <atl/abc/TomlLoadable.hpp> //TomlLoadable, toml::value
#include <atl/util/Functions.hpp> //hash
#include <atl/game_tools/Tile.hpp> //Tile, ITileInfo, TileInfoFactory, TileInfoContainer
#include <atl/game_tools/Map.hpp> //Map

namespace atl {
	//TODO: atl::IDrawable inherit
	class TileMap : public sf::Drawable, public TomlLoadable {
	public:
		TileMap();

		void setTile(Tile value, id_t infoId, size_t x, size_t y);

		Tile& getTile(size_t x, size_t y);
		const Tile& getTile(size_t x, size_t y) const;

		virtual bool load(const toml::value& data) override;

	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		TileInfoContainer _info;
		Map _storage;
	};
}