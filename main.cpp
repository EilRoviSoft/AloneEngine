#include <atl/game_tools/TileMap.hpp>

//sf::RenderWindow window(sf::VideoMode(800, 600), "Simple Window");
using namespace atl;

int main() {
	std::ifstream fin("res/a0a0.wld");

	game_tools::Map map;
	map.loadFromStream(fin);

	fin.close();

	return 0;
}