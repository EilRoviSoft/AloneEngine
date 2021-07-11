#include "Tile.hpp"

//Cluster
atl::Cluster::Cluster(size_t id) : value((Type) id) {}
atl::Cluster::Cluster(Type value) : value(value) {}

atl::Cluster::operator Type() {
	return value;
}

atl::Cluster atl::Cluster::fromString(const std::string& source) {
	switch_str(source.c_str()) {
		case_str("ba"): return BlockSolid;
		case_str("bi"): return BlockInside;
		case_str("bu"): return BlockUp;
		case_str("br"): return BlockRight;
		case_str("bd"): return BlockDown;
		case_str("bl"): return BlockLeft;
		case_str("bv"): return BlockVertical;
		case_str("bh"): return BlockHorizontal;
		case_str("bdi"): return BlockDownInverse;
		case_str("bli"): return BlockLeftInverse;
		case_str("bui"): return BlockUpInverse;
		case_str("bri"): return BlockRightInverse;
		case_str("t1i"): return Triangle1Inside;
		case_str("t2i"): return Triangle2Inside;
		case_str("t3i"): return Triangle3Inside;
		case_str("t4i"): return Triangle4Inside;
		case_str("t1le"): return Triangle1LeftEdge;
		case_str("t2le"): return Triangle2LeftEdge;
		case_str("t3le"): return Triangle3LeftEdge;
		case_str("t4le"): return Triangle4LeftEdge;
		case_str("t1re"): return Triangle1RightEdge;
		case_str("t2re"): return Triangle2RightEdge;
		case_str("t3re"): return Triangle3RightEdge;
		case_str("t4re"): return Triangle4RightEdge;
		case_str("t1s"): return Triangle1Solid;
		case_str("t2s"): return Triangle2Solid;
		case_str("t3s"): return Triangle3Solid;
		case_str("t4s"): return Triangle4Solid;
		default: return BlockSolid;
	}
}
std::string atl::Cluster::toString(Cluster what) {
	switch (what) {
	case BlockSolid: return "ba";
	case BlockInside: return "bi";
	case BlockUp: return "bi";
	case BlockRight: return "br";
	case BlockDown: return "bd";
	case BlockLeft: return "bl";
	case BlockVertical: return "bv";
	case BlockHorizontal: return "bh";
	case BlockDownInverse: return "bdi";
	case BlockLeftInverse: return "bli";
	case BlockUpInverse: return "bui";
	case BlockRightInverse: return "bri";
	case Triangle1Inside: return "t1i";
	case Triangle2Inside: return "t2i";
	case Triangle3Inside: return "t3i";
	case Triangle4Inside: return "t4i";
	case Triangle1LeftEdge: return "t1le";
	case Triangle2LeftEdge: return "t2le";
	case Triangle3LeftEdge: return "t3le";
	case Triangle4LeftEdge: return "t4le";
	case Triangle1RightEdge: return "t1re";
	case Triangle2RightEdge: return "t2re";
	case Triangle3RightEdge: return "t3re";
	case Triangle4RightEdge: return "t4re";
	case Triangle1Solid: return "t1s";
	case Triangle2Solid: return "t2s";
	case Triangle3Solid: return "t3s";
	case Triangle4Solid: return "t4s";
	}
}

//ITileInfo
atl::ITileInfo::ITileInfo(const sf::Texture& texture) : _texture(texture) {}

bool atl::ITileInfo::load(const pugi::xml_node& data) {
	_variants = data.attribute("variants").as_uint(1);
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
		const auto& texture = context.textures.at(it.attribute("image").as_string());
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

void atl::Tile::setCluster(id_t cluster) {
	if (cluster < _info->_variants)
		_cluster = cluster;
	else
		_cluster = 0;
}
void atl::Tile::setInfo(TileInfo info) {
	_info = info;
}