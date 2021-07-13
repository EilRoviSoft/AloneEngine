#pragma once
//sf
#include <SFML/Graphics.hpp> //Sprite, RenderTarget, RenderStates, Vector2

//std
#include <cstdint> //uint8_t
#include <memory> //shared_ptr
#include <string> //string

//uxl
#include <uxl/RequestQueue.hpp> //RequestQueue

//atl
#include <atl/abc/TomlLoadable.hpp> //TomlLoadable, toml::value
#include <atl/abc/Renderable.hpp> //IComplexRenderable
#include <atl/abc/Updatable.hpp> //IReceivable
#include <atl/game_tools/Tile.hpp> //Tile, ITileInfo, TileInfoFactory, TileInfoContainer
#include <atl/game_tools/Map.hpp> //Map
#include <atl/game_tools/Core.hpp> //context

namespace atl {
	using TileMapPoints = uxl::RequestQueue <sf::Vector2 <size_t>>;

	//TODO: Make it centralized
	//TODO: Animated tiles support
	class TileMap : public IComplexRenderable, public TomlLoadable, public IReceivable <TileMapPoints> {
	public:
		TileMap();

		void setTile(size_t x, size_t y, Tile value, TileInfo info);

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
		Map _storage;
		TileMapPoints _onUpdateTiles;
	};
}