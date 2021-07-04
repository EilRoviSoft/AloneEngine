#include "game_tools\GameWindow.hpp"

atl::GameWindow::GameWindow(sf::Vector2u size, const std::string& title) :
	sf::RenderWindow(sf::VideoMode(size.x, size.y), title) {}