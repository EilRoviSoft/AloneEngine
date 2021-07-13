#include <thread>
#include <atl/game_tools/GameWindow.hpp>
#include <atl/game_tools/TileMap.hpp>

namespace atl {
	Core context;
}

using namespace atl;

const auto framerate = 60ull;
const auto period = 1000.f / framerate;

GameWindow window(sf::Vector2u(800, 600), "Simple Window", framerate);

int main() {
	context.textures.loadFromFile("res/settings/textures.toml");
	context.tiles.loadFromFile("res/game/tile-info.xml");

	TileMap map;
	map.loadFromFile("res/saves/Eil/basic.toml");

	sf::Clock clock;
	//sf::Image frame = window.capture();

	window.predraw(map);

	while (window.isOpen()) {
		clock.restart();
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.draw(map);

		auto time = clock.getElapsedTime();
		auto s = time.asSeconds();
		auto ms = time.asMilliseconds();
		auto mcs = time.asMicroseconds();

		int64 sleep_time = period - ms;
		if (sleep_time > 0)
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));

		window.display();
		//frame = window.capture();
	}

	return 0;
}