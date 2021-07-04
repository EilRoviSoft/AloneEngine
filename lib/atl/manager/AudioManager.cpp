#include "AudioManager.hpp"

atl::AudioManager::AudioManager(const std::string& filename) {
	loadFromFile(filename);
}

void atl::AudioManager::loadItem(const std::string& folder, const toml::value& data) {
	size_t key = hash(data.as_string());
	m_content.insert({ key, sf::SoundBuffer() });

	auto it = m_content.find(key);
	if (it != m_content.end())
		it->second.loadFromFile(folder + data.as_string().str);
}