#pragma once
//sf
#include <SFML/Graphics.hpp> //Drawable, Sprite, Texture
#include <SFML/System.hpp> //Vector2i, IntRect

//std
#include <cstdint> //uint8_t
#include <memory> //shared_ptr
#include <map> //map
#include <string> //string

//atl
#define XML_LOADABLE
#include <atl/abc/XmlLoadable.hpp> //abc::XmlLoadable, pugi::xml_node
#include <atl/abc/TomlLoadable.hpp> //abc::TomlLoadable, toml::value
#include <atl/util/Functions.hpp> //util::hash
#include <atl/game_tools/Core.hpp> //core

//xtl
#include <xtl/Matrix.hpp> //Matrix

namespace atl::game {
	using id_t = uint8_t;
	const sf::Vector2i tile(16, 16), offset(2, 2);
	const id_t inRow = 28;

	class ITileInfo : public abc::XmlLoadable {
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
			std::string type = data.attribute("type").as_string();
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
	public:
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
		//28 in row
		id_t _cluster;
	};

	class TileMap : public sf::Drawable, public abc::TomlLoadable {
	public:
		TileMap() {}

		void setTile(Tile value, id_t infoId, size_t x, size_t y) {
			value._info = _info[infoId];
			_storage.at(x, y) = value;
		}

		Tile& getTile(size_t x, size_t y) {
			return _storage.at(x, y);
		}
		const Tile& getTile(size_t x, size_t y) const {
			return _storage.at(x, y);
		}

		virtual bool load(const toml::value& data) override {
			if (!_info.loadFromFile(data.at("tile-info").as_string()))
				return false;

			return true;
		}

	protected:
		//TODO: predraw
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
			sf::Sprite atlas;

			for (size_t i = 0; i != _storage.getColumns(); i++)
				for (size_t j = 0; j != _storage.getRows(); j++) {
					atlas.setTexture(_storage.at(i, j)->_texture);
					atlas.setTextureRect(_storage.at(i, j).getRegion());
					atlas.setPosition(i * tile.x, j * tile.y);

					target.draw(atlas, states);
				}
		}

	private:
		class : public abc::XmlLoadable {
		public:
			TileInfo& operator[](size_t id) {
				return _content.at(id);
			}
			const TileInfo& operator[](size_t id) const {
				return _content.at(id);
			}

			virtual bool load(const pugi::xml_node& data) override {
				for (const auto& it : data) {
					const auto& texture = atl::core.textures.at(it.attribute("image").as_string());
					_content.insert({ util::hash(it.name()), TileInfoFactory::create(it, texture) });
				}

				return true;
			}

		private:
			std::map <size_t, TileInfo> _content;
		} _info;

		xtl::Matrix <Tile> _storage;
	};
}