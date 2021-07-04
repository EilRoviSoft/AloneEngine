#pragma once
//sf
#include <SFML/Graphics.hpp> //Drawable, Sprite, RenderTarget, RenderStates

//std
#include <cstdint> //uint8_t
#include <memory> //shared_ptr
#include <map> //map
#include <string> //string

//atl
#include <atl/abc/XmlLoadable.hpp> //abc::XmlLoadable, pugi::xml_node
#include <atl/abc/TomlLoadable.hpp> //abc::TomlLoadable, toml::value
#include <atl/util/Functions.hpp> //util::hash
#include <atl/game_tools/Core.hpp> //core
#include <atl/game_tools/Tile.hpp> //game_tools::Tile, game_tools::ITileInfo, game_tools::TileInfoFactory
#include <atl/game_tools/Map.hpp> //util::Map

namespace atl::game_tools {
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
			bool infoLoadResult = _info.loadFromFile(data.at("tile-info").as_string());
			bool storageLoadResult = _storage.loadFromFile((std::string) data.at("saves-folder").as_string() + "main.wld");

			return !infoLoadResult || !storageLoadResult;
		}

	protected:
		//TODO: predraw
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
			sf::Sprite atlas;

			for (size_t i = 0; i != _storage.cols(); i++)
				for (size_t j = 0; j != _storage.rows(); j++) {
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
					_content.insert({ it.attribute("id").as_ullong(), TileInfoFactory::create(it, texture) });
				}

				return true;
			}

		private:
			std::map <size_t, TileInfo> _content;
		} _info;

		Map _storage;
	};
}