#include <atl/game_tools/GameWindow.hpp>
#include <atl/game_tools/TileMap.hpp>

namespace atl {
	Core context;
}

using namespace atl;

GameWindow window(sf::Vector2u(800, 600), "Simple Window");

int main() {
	context.textures.loadFromFile("res/settings/textures.toml");
	TileMap map;
	map.loadFromFile("res/saves/Eil/tilemap.toml");

	sf::Clock clock;

	window.predraw(map);

	while (window.isOpen()) {
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();
	}

	return 0;
}