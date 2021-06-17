#pragma once
//sf
#include <SFML/Graphics.hpp> //Font

namespace atl {
	class Core {
	public:
		sf::Font font;
	};

	static Core core;
}