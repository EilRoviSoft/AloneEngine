#pragma once
//sf
#include <SFML/Graphics.hpp> //Font

//atl
#include <atl/manager/TextureManager.hpp> //TextureManager

namespace atl {
	struct Core {
		sf::Font font;
		TextureManager textures;
	};

	static Core core;
}