#pragma once
//sf
#include <SFML/Graphics.hpp> //Font

//atl
#include <atl/manager/TextureManager.hpp> //manager::TextureManager

namespace atl {
	struct Core {
		sf::Font font;
		manager::TextureManager textures;
	};

	static Core core;
}