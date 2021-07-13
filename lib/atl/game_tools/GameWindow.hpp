#pragma once
//sf
#include <SFML/Graphics/RenderWindow.hpp> //RenderWindow
#include <SFML/Graphics/RenderStates.hpp> //RenderStates
#include <SFML/System/Vector2.hpp> //Vector2f

//std
#include <string> //string

//atl
#include <atl/abc/Renderable.hpp> //IRenderable, IComplexRenderable

namespace atl {
	class GameWindow : public sf::RenderWindow {
	public:
		GameWindow(sf::Vector2u size, const std::string& title, size_t framerate = 60);

		void predraw(const IComplexRenderable& what, const sf::RenderStates& states = sf::RenderStates::Default);
	};
}