#pragma once
//std
#include <vector> //vector
#include <exception> //exception
#include <iostream> //cerr
#include <fstream> //ofstream

//atl
#include <atl/util/Matrix.hpp> //util::Matrix
#include <atl/game_tools/Tile.hpp> //game_tools::Tile
//#include <atl/abc/FlatLoadable.hpp> //abc::FlatLoadable
#include <atl/abc/Loadable.hpp> //abc::ILoadable

namespace atl::game_tools {
	class Map : public util::Matrix <Tile>, abc::ILoadable <std::vector <Tile>&&> {
	public:
		Map() {}

		//TODO
		bool loadFromStream(std::istream& in) override {
			return load(std::vector <Tile>());
		}

		//TODO
		bool load(std::vector <Tile>&& data) override {
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