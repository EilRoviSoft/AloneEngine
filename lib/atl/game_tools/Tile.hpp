#pragma once
//sf
#include <SFML/System/Vector2.hpp> //Vector2i
#include <SFML/Graphics/Rect.hpp> //IntRect
#include <SFML/Graphics/Texture.hpp> //Texture

//std
#include <cstdint> //uint8_t
#include <string> //string
#include <map> //map

//atl
#include <atl/abc/XmlLoadable.hpp> //XmlLoadable, pugi::xml_node
#include <atl/game_tools/Core.hpp> //core

namespace atl {
	using id_t = uint8_t;
	const sf::Vector2i tile(16, 16), offset(2, 2);
	const id_t inRow = 28;

	class ITileInfo : public XmlLoadable {
		friend class TileMap;
		friend class Tile;
	public:
		ITileInfo(const sf::Texture& texture);

		virtual bool load(const pugi::xml_node& data) override;

	private:
		const sf::Texture& _texture;
		id_t _max;
		std::string _name;
	};
	using TileInfo = std::shared_ptr <ITileInfo>;

	class TileInfoContainer : public XmlLoadable {
	public:
		TileInfo& operator[](size_t id);
		const TileInfo& operator[](size_t id) const;

		virtual bool load(const pugi::xml_node& data) override;

	private:
		std::map <size_t, TileInfo> _content;
	};

	struct TileInfoFactory {
		static TileInfo create(const pugi::xml_node& data, const sf::Texture& texture);
	};

	class Tile {
		friend class TileMap;
		friend class Map;
	public:
		Tile(const id_t& cluster = 0);
		Tile(const id_t& cluster, TileInfo info);

		const ITileInfo* operator->() const;

		const id_t& getCluster() const;

		sf::IntRect getRegion() const;

	private:
		id_t& getCluster();
		void setCluster(id_t cluster);

		TileInfo _info;
		//28 in a row
		id_t _cluster;
	};
}