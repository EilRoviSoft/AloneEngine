#include <atl/game_tools/TileMap.hpp>

//sf::RenderWindow window(sf::VideoMode(800, 600), "Simple Window");
using namespace atl;

int main() {
	std::ofstream fout("res/a0a0.wld");

	game_tools::Map::generate(fout, 10, 10);

	fout.close();

	return 0;
}