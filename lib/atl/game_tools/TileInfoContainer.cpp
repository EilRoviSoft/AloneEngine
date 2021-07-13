#include "TileInfoContainer.hpp"
//TileInfoContainer
atl::TileInfo& atl::TileInfoContainer::operator[](size_t id) {
	return _content.at(id);
}
const atl::TileInfo& atl::TileInfoContainer::operator[](size_t id) const {
	return _content.at(id);
}

bool atl::TileInfoContainer::load(const pugi::xml_node& data) {
	for (const auto& it : data) {
		auto texture_name = it.attribute("image").as_string();
		_content.insert({ it.attribute("id").as_ullong(), TileInfoFactory::create(it, texture_name) });
	}

	return true;
}