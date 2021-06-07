#pragma once
//std
#include <string> //string

//sfml
#include <SFML/Audio/SoundBuffer.hpp> //SoundBuffer

//toml
#include <toml/include.hpp> //value

//atl
#include <atl/abc/Manager.hpp> //IManager

namespace atl::manager {
	class AudioManager : public atl::abc::IManager <sf::SoundBuffer> {
	protected:
		void loadItem(const std::string& _folder, const toml::value& _it) override {
			this->m_content.insert();
		}
	};
}