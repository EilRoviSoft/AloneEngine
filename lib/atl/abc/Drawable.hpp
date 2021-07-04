#pragma once
//sf
#include <SFML/Graphics/Drawable.hpp> //Drawable
#include <SFML/Graphics/RenderTarget.hpp> //RenderTarget
#include <SFML/Graphics/RenderStates.hpp> //RenderStates

namespace atl::abc {
	class IDrawable : public sf::Drawable {
		//friend class GameWindow
	protected:
		virtual void predraw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const = 0;
	};
}