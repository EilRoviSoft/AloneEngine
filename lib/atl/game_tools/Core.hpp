#pragma once
//sf
#include <SFML/Graphics.hpp> //Font

//atl
#include <atl/manager/TextureManager.hpp> //TextureManager
#include <atl/game_tools/TileInfoContainer.hpp> //TileInfoContainer

namespace atl {
	struct Core {
		sf::Font font;
		TextureManager textures;
		TileInfoContainer tiles;
	};

	extern Core context;
}