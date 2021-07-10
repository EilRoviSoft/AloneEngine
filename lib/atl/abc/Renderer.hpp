#pragma once
//sf
#include <atl/game_tools/GameWindow.hpp> //GameWindow

namespace atl {
	class IRenderer {
	public:
		virtual void prerender(GameWindow& target, sf::RenderStates states) const = 0;
		virtual void render(GameWindow& target, sf::RenderStates states) const = 0;
	};
}