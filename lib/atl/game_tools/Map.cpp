#include "Map.hpp"

bool atl::Map::loadFromStream(std::istream& in) {
	return load(FlatLoader::load <uint16_t, uint8_t>(in));
}
bool atl::Map::load(std::vector<id_t>&& data) {
	resize(data[0], data[1]);

	for (size_t i = 0; i != size(); i++) {
		at(i) = data[i * 2 + 2];
		at(i).setCluster(data[i * 2 + 3]);
	}

	return true;
}

void atl::Map::generate(std::ofstream& file, size_t cols, size_t rows, id_t inner, id_t outer) {
	/*file << (cols * rows + 2) << '\n';
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
		file << outer << ' ';*/
}