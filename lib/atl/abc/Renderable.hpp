#pragma once
//sf
#include <SFML/Graphics/Drawable.hpp> //Drawable
#include <SFML/Graphics/RenderTarget.hpp> //RenderTarget
#include <SFML/Graphics/RenderStates.hpp> //RenderStates

namespace atl {
	using IRenderable = sf::Drawable;

	class IComplexRenderable : public IRenderable {
		friend class IRenederer;
		friend class GameWindow;
	protected:
		virtual void predraw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	};
}