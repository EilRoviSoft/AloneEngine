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
		AudioManager(const std::string& filename);

	protected:
		void loadItem(const std::string& folder, const toml::value& data) override;
	};
}