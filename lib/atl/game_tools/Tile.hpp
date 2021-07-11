#pragma once
//sf
#include <SFML/System/Vector2.hpp> //Vector2i
#include <SFML/Graphics/Rect.hpp> //IntRect
#include <SFML/Graphics/Texture.hpp> //Texture
#include <SFML/Graphics/Drawable.hpp> //Drawable

//std
#include <cstdint> //uint8_t
#include <string> //string
#include <map> //map

//uxl
#include <uxl/switch_string.hpp> //switch_str, case_str

//atl
#include <atl/abc/XmlLoadable.hpp> //XmlLoadable, pugi::xml_node
#include <atl/game_tools/Core.hpp> //Core
#include <atl/util/Functions.hpp> //hash

namespace atl {
	using id_t = uint8_t;
	const sf::Vector2i tile(16, 16), offset(2, 2);
	const id_t inRow = 28;

	//2-UP-3
	//L----R
	//T----T
	//1-DN-4
	struct Cluster {
		enum Type {
			BlockSolid = 0,
			BlockInside,
			BlockUp,
			BlockRight,
			BlockDown,
			BlockLeft,
			BlockVertical,
			BlockHorizontal,
			BlockDownInverse,
			BlockLeftInverse,
			BlockUpInverse,
			BlockRightInverse,
			Triangle1Inside,
			Triangle2Inside,
			Triangle3Inside,
			Triangle4Inside,
			Triangle1LeftEdge,
			Triangle2LeftEdge,
			Triangle3LeftEdge,
			Triangle4LeftEdge,
			Triangle1RightEdge,
			Triangle2RightEdge,
			Triangle3RightEdge,
			Triangle4RightEdge,
			Triangle1Solid,
			Triangle2Solid,
			Triangle3Solid,
			Triangle4Solid
		};

		Cluster(size_t id = 0);
		Cluster(Type value);

		operator Type();

		static Cluster fromString(const std::string& source);
		static std::string toString(Cluster what);

		Type value;
	};

	class ITileInfo : public XmlLoadable {
		friend class TileMap;
		friend class Tile;
	public:
		ITileInfo(const sf::Texture& texture);

		virtual bool load(const pugi::xml_node& data) override;

	private:
		const sf::Texture& _texture;
		id_t _variants;
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
	public:
		Tile(const id_t& cluster = 0);
		Tile(const id_t& cluster, TileInfo info);

		const ITileInfo* operator->() const;

		const id_t& getCluster() const;
		sf::IntRect getRegion() const;

		void setCluster(id_t cluster);
		void setInfo(TileInfo info);

	private:
		TileInfo _info;
		//28 in a row
		id_t _cluster;
	};
}