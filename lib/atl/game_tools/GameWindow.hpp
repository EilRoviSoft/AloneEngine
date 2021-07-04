#pragma once
//sf
#include <SFML/Graphics/RenderWindow.hpp> //RenderWindow
#include <SFML/System/Vector2.hpp> //Vector2f

//std
#include <string> //string

//atl

namespace atl::game_tools {
	//TODO: useless now
	class GameWindow : public sf::RenderWindow {
	public:
		GameWindow(sf::Vector2u size, const std::string& title) : 
			sf::RenderWindow(sf::VideoMode(size.x, size.y), title) {}
	};
}