#include "Tile.hpp"

//ITileInfo
atl::ITileInfo::ITileInfo(const sf::Texture& texture) : _texture(texture) {}

bool atl::ITileInfo::load(const pugi::xml_node& data) {
	_max = data.attribute("variants").as_uint(1);
	_name = data.attribute("display").as_string();

	return true;
}

//ITileInfoFactory
atl::TileInfo atl::TileInfoFactory::create(const pugi::xml_node& data, const sf::Texture& texture) {
	std::string type = data.name();
	auto result = TileInfo(nullptr);

	if (type == "ITileInfo") {
		result.reset(new ITileInfo(texture));
		result->load(data);
	}

	return result;
}

//TileInfoContainer
atl::TileInfo& atl::TileInfoContainer::operator[](size_t id) {
	return _content.at(id);
}
const atl::TileInfo& atl::TileInfoContainer::operator[](size_t id) const {
	return _content.at(id);
}

bool atl::TileInfoContainer::load(const pugi::xml_node& data) {
	for (const auto& it : data) {
		const auto& texture = atl::core.textures.at(it.attribute("image").as_string());
		_content.insert({ it.attribute("id").as_ullong(), TileInfoFactory::create(it, texture) });
	}

	return true;
}

//Tile
atl::Tile::Tile(const id_t& cluster) : _cluster(cluster), _info(nullptr) {}
atl::Tile::Tile(const id_t& cluster, TileInfo info) : _cluster(cluster), _info(info) {}

const atl::ITileInfo* atl::Tile::operator->() const {
	return _info.get();
}

const atl::id_t& atl::Tile::getCluster() const {
	return _cluster;
}

sf::IntRect atl::Tile::getRegion() const {
	auto row = (id_t) _cluster % inRow;
	auto column = (id_t) _cluster / inRow;

	return sf::IntRect(offset.x * (row + 1) + tile.x * row, offset.y * (row + 1) + tile.y * row, tile.x, tile.y);
}

atl::id_t& atl::Tile::getCluster() {
	return _cluster;
}
void atl::Tile::setCluster(id_t cluster) {
	if (cluster < _info->_max)
		_cluster = cluster;
	else
		_cluster = 0;
}
