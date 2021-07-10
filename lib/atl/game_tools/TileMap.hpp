#pragma once
//sf
#include <SFML/Graphics.hpp> //Sprite, RenderTarget, RenderStates

//std
#include <cstdint> //uint8_t
#include <memory> //shared_ptr
#include <map> //map
#include <list> //list
#include <string> //string

//atl
#include <atl/abc/XmlLoadable.hpp> //XmlLoadable, pugi::xml_node
#include <atl/abc/TomlLoadable.hpp> //TomlLoadable, toml::value
#include <atl/abc/Renderable.hpp> //IComplexRenderable
#include <atl/abc/Updatable.hpp> //IReceivable
#include <atl/util/Functions.hpp> //hash
#include <atl/game_tools/Tile.hpp> //Tile, ITileInfo, TileInfoFactory, TileInfoContainer
#include <atl/game_tools/Map.hpp> //Map
#include <atl/game_tools/Core.hpp> //Core

namespace atl {
	using TileMapPoints = std::list <sf::Vector2 <size_t>>;

	//TODO: Animated tiles support
	class TileMap : public IComplexRenderable, public TomlLoadable, public IReceivable <TileMapPoints> {
	public:
		TileMap();

		void setTile(Tile value, id_t infoId, size_t x, size_t y);

		Tile& getTile(size_t x, size_t y);
		const Tile& getTile(size_t x, size_t y) const;

		virtual bool load(const toml::value& data) override;

		virtual void receive(const IPostable <TileMapPoints>& what) override;

	protected:
		//TODO: realize it using sf::Verticies
		virtual void predraw(sf::RenderTarget& target, sf::RenderStates states) const override;
		//TODO: realize it using sf::Verticies
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		TileInfoContainer _info;
		Map _storage;
		TileMapPoints _onUpdateTiles;
	};
}