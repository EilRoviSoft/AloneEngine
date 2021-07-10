#pragma once
//std
#include <vector> //vector
#include <exception> //exception
#include <iostream> //cerr
#include <fstream> //ofstream

//atl
#include <atl/util/Matrix.hpp> //Matrix
#include <atl/game_tools/Tile.hpp> //Tile
#include <atl/abc/Loadable.hpp> //ILoadable
#include <atl/util/FlatLoader.hpp> //FlatLoader

namespace atl {
	class Map : public Matrix <Tile>, public ILoadable <std::vector <id_t>&&> {
		friend class TileMap;
	public:
		Map() {}

		bool loadFromStream(std::istream& in) override;
		bool load(std::vector <id_t>&& data) override;

		//TODO: rewrite
		static void generate(std::ofstream& file, size_t cols, size_t rows, id_t inner = '0', id_t outer = '1');
	};
}