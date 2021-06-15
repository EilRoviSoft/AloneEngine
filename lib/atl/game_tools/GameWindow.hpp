#pragma once
//sf
#include <SFML/Graphics/RenderWindow.hpp> //RenderWindow
#include <SFML/System/Vector2.hpp> //Vector2f

//std
#include <string> //string

namespace atl::game_tools {
	//TODO: useless now
	class GameWindow : public sf::RenderWindow {
	public:
		GameWindow(sf::Vector2u _size, const std::string& _title) : 
			sf::RenderWindow(sf::VideoMode(_size.x, _size.y), _title) {}
	};
}