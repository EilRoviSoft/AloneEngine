#pragma once
//sf
#include <SFML/System/Vector2.hpp> //Vector2i
#include <SFML/Graphics/Rect.hpp> //IntRect
#include <SFML/Graphics/Texture.hpp> //Texture

//std
#include <cstdint> //uint8_t
#include <string> //string

//atl
#include <atl/abc/XmlLoadable.hpp> //XmlLoadable, pugi::xml_node

namespace atl {
	using id_t = uint8_t;
	const sf::Vector2i tile(16, 16), offset(2, 2);
	const id_t inRow = 28;

	class ITileInfo : public XmlLoadable {
		friend class TileMap;
		friend class Tile;
	public:
		ITileInfo(const sf::Texture& texture) : _texture(texture) {}

		virtual bool load(const pugi::xml_node& data) override {
			_max = data.attribute("variants").as_uint(1);
			_name = data.attribute("display").as_string();

			return true;
		}

	private:
		const sf::Texture& _texture;
		id_t _max;
		std::string _name;
	};
	using TileInfo = std::shared_ptr <ITileInfo>;

	struct TileInfoFactory {
		static TileInfo create(const pugi::xml_node& data, const sf::Texture& texture) {
			std::string type = data.name();
			auto result = TileInfo(nullptr);

			if (type == "ITileInfo") {
				result.reset(new ITileInfo(texture));
				result->load(data);
			}

			return result;
		}
	};

	class Tile {
		friend class TileMap;
		friend class Map;
	public:
		Tile(const id_t& cluster = 0) : _cluster(cluster), _info(nullptr) {}
		Tile(const id_t& cluster, TileInfo info) : _cluster(cluster), _info(info) {}

		const ITileInfo* operator->() const {
			return _info.get();
		}

		const id_t& getCluster() const {
			return _cluster;
		}

		sf::IntRect getRegion() const {
			auto row = (id_t) _cluster % inRow;
			auto column = (id_t) _cluster / inRow;

			return sf::IntRect(offset.x * (row + 1) + tile.x * row, offset.y * (row + 1) + tile.y * row, tile.x, tile.y);
		}

	private:
		id_t& getCluster() {
			return _cluster;
		}
		void setCluster(id_t cluster) {
			if (cluster < _info->_max)
				_cluster = cluster;
			else
				_cluster = 0;
		}

		TileInfo _info;
		//28 in a row
		id_t _cluster;
	};
}