#pragma once
//std
#include <string> //string

//sfml
#include <SFML/Audio/SoundBuffer.hpp> //SoundBuffer

//atl
#include <atl/abc/Manager.hpp> //IManager, toml::value
#include <atl/util/Functions.hpp> //hash

namespace atl {
	class AudioManager : public IManager <sf::SoundBuffer> {
	public:
		AudioManager(const std::string& filename) {
			loadFromFile(filename);
		}

	protected:
		void loadItem(const std::string& folder, const toml::value& data) override {
			size_t key = util::hash(data.as_string());
			m_content.insert({ key, sf::SoundBuffer() });

			auto it = m_content.find(key);
			if (it != m_content.end())
				it->second.loadFromFile(folder + data.as_string().str);
		}
	};
}