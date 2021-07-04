#pragma once
//std
#include <string> //string

//sfml
#include <SFML/Graphics/Texture.hpp> //Texture

//atl
#include <atl/abc/Manager.hpp> //IManager, toml::value
#include <atl/util/Functions.hpp> //hash

namespace atl {
	class TextureManager : public IManager <sf::Texture> {
	public:
		TextureManager();
		TextureManager(const std::string& filename);

	protected:
		void loadItem(const std::string& folder, const toml::value& data) override;
	};
}