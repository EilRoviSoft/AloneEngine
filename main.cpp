#include <atl/game_tools/TileMap.hpp>

//sf::RenderWindow window(sf::VideoMode(800, 600), "Simple Window");
using namespace atl;

int main() {
	core.textures.loadFromFile("res/settings/textures.toml");

	game::TileMap tm;
	tm.loadFromFile("res/settings/tilemap.toml");

	return 0;
}