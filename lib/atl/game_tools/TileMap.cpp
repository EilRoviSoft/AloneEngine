#include "TileMap.hpp"

atl::TileMap::TileMap() {}

void atl::TileMap::setTile(size_t x, size_t y, Tile value, TileInfo info) {
	value.setInfo(info);
	_storage.at(x, y) = value;
}

atl::Tile& atl::TileMap::getTile(size_t x, size_t y) {
	return _storage.at(x, y);
}
const atl::Tile& atl::TileMap::getTile(size_t x, size_t y) const {
	return _storage.at(x, y);
}

bool atl::TileMap::load(const toml::value& data) {
	bool storageLoadResult = _storage.loadFromFile((std::string) data.at("saves-folder").as_string() + "main.wld");

	return storageLoadResult;
}

void atl::TileMap::receive(const IPostable <TileMapPoints>& what) {
	_onUpdateTiles.merge(what.post());
}

void atl::TileMap::predraw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite atlas;

	for (size_t i = 0; i != _storage.cols(); i++)
		for (size_t j = 0; j != _storage.rows(); j++) {
			atlas.setTexture(_storage.at(i, j)->_texture);
			atlas.setTextureRect(_storage.at(i, j).getRegion());
			atlas.setPosition(i * tile.x, j * tile.y);

			target.draw(atlas, states);
		}
}
void atl::TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite atlas;

	for (const auto& it : _onUpdateTiles) {
		atlas.setTexture(_storage.at(it.x, it.y)->_texture);
		atlas.setTextureRect(_storage.at(it.x, it.y).getRegion());
		atlas.setPosition(it.x * tile.x, it.y * tile.y);

		target.draw(atlas, states);
	}
}