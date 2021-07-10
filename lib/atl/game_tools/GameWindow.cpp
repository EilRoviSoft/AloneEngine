#include "GameWindow.hpp"

atl::GameWindow::GameWindow(sf::Vector2u size, const std::string& title) :
	sf::RenderWindow(sf::VideoMode(size.x, size.y), title) {}

void atl::GameWindow::predraw(const IComplexRenderable& what, const sf::RenderStates& states) {
	what.predraw(*this, states);
}
