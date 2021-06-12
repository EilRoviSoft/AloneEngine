#pragma once
//std
#include <string> //string

//sfml
#include <SFML/Audio/SoundBuffer.hpp> //SoundBuffer

//toml
#include <toml/value.hpp> //value

//atl
#include <atl/abc/Manager.hpp> //manager::IManager
#include <atl/util/Functions.hpp> //util::hash

namespace atl::manager {
	class AudioManager : public atl::abc::IManager <sf::SoundBuffer> {
	protected:
		void loadItem(const std::string& _folder, const toml::value& _it) override {
			size_t key = util::hash(_it.as_string());
			this->m_content.insert({ key, sf::SoundBuffer() });

			auto it = this->m_content.find(key);
			if (it != this->m_content.end())
				it->second.loadFromFile(_folder + _it.as_string().str);
		}

	public:
		AudioManager(const std::string& _filename) {
			this->loadFromFile(_filename);
		}
	};
}