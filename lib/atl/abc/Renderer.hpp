#pragma once
//sf
#include <SFML/Graphics/RenderWindow.hpp> //RenderWindow

namespace atl::abc {
	class IRenderer {
	public:
		virtual void render(sf::RenderWindow& window) const = 0;
	};
}