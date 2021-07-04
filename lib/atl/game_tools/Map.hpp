#pragma once
//std
#include <vector> //vector
#include <exception> //exception
#include <iostream> //cerr
#include <fstream> //ofstream

//atl
#include <atl/util/Matrix.hpp> //Matrix
#include <atl/game_tools/Tile.hpp> //Tile
//#include <atl/abc/FlatLoadable.hpp> //FlatLoadable
#include <atl/abc/Loadable.hpp> //ILoadable
#include <atl/util/FlatLoader.hpp> //FlatLoader

namespace atl {
	class Map : public Matrix <Tile>, public ILoadable <std::vector <id_t>&&> {
	public:
		Map() {}

		bool loadFromStream(std::istream& in) override {
			return load(util::FlatLoader::load <uint16_t, uint8_t>(in));
		}
		bool load(std::vector <id_t>&& data) override {
			resize(data[0], data[1]);

			for (size_t i = 0; i != size(); i++)
				at(i) = data[i + 2];
			
			return true;
		}

		static void generate(std::ofstream& file, size_t cols, size_t rows, id_t inner = '0', id_t outer = '1') {
			file << (cols * rows + 2) << '\n';
			file << cols << ' ' << rows << '\n';

			for (size_t i = 0; i != cols; i++)
				file << outer << ' ';
			file << '\n';

			for (size_t i = 1; i != rows - 1; i++) {
				file << outer << ' ';
				
				for (size_t j = 1; j != cols - 1; j++)
					file << inner << ' ';

				file << outer << " \n";
			}

			for (size_t i = 0; i != cols; i++)
				file << outer << ' ';
		}
	};
}