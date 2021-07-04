#include "TextureManager.hpp"

atl::TextureManager::TextureManager() {}
atl::TextureManager::TextureManager(const std::string& filename) {
	loadFromFile(filename);
}

void atl::TextureManager::loadItem(const std::string& folder, const toml::value& data) {
	size_t key = hash <std::string>(data.as_string());
	m_content.insert({ key, sf::Texture() });

	auto it = m_content.find(key);
	if (it != m_content.end())
		it->second.loadFromFile(folder + data.as_string().str);
}
