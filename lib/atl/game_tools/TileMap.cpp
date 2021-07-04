#include "TileMap.hpp"

atl::TileMap::TileMap() {}

void atl::TileMap::setTile(Tile value, id_t infoId, size_t x, size_t y) {
	value._info = _info[infoId];
	_storage.at(x, y) = value;
}

atl::Tile& atl::TileMap::getTile(size_t x, size_t y) {
	return _storage.at(x, y);
}
const atl::Tile& atl::TileMap::getTile(size_t x, size_t y) const {
	return _storage.at(x, y);
}

bool atl::TileMap::load(const toml::value& data) {
	bool infoLoadResult = _info.loadFromFile(data.at("tile-info").as_string());
	bool storageLoadResult = _storage.loadFromFile((std::string) data.at("saves-folder").as_string() + "main.wld");

	return !infoLoadResult || !storageLoadResult;
}

void atl::TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::Sprite atlas;

	for (size_t i = 0; i != _storage.cols(); i++)
		for (size_t j = 0; j != _storage.rows(); j++) {
			atlas.setTexture(_storage.at(i, j)->_texture);
			atlas.setTextureRect(_storage.at(i, j).getRegion());
			atlas.setPosition(i * tile.x, j * tile.y);

			target.draw(atlas, states);
		}
}