#include "GameWindow.hpp"

atl::GameWindow::GameWindow(sf::Vector2u size, const std::string& title, size_t framerate) :
sf::RenderWindow(sf::VideoMode(size.x, size.y), title) {
	setFramerateLimit(framerate);
}

void atl::GameWindow::predraw(const IComplexRenderable& what, const sf::RenderStates& states) {
	what.predraw(*this, states);
}
