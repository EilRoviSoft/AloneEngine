#pragma once
//std
#include <vector> //vector

namespace xtl {
	template <class Type>
	class Matrix {
	public:
		Matrix(size_t columns = 0, size_t rows = 0, const Type& init = Type()) : 
			_storage(columns * rows, init), _columns(columns), _rows(rows) {}

		Type& at(size_t column, size_t row) {
			return _storage.at(column * _columns + row);
		}
		const Type& at(size_t column, size_t row) const {
			return _storage.at(column * _columns + row);
		}

		void reserve(size_t columns, size_t rows) {
			_storage.reserve(rows * columns);
			_columns = columns;
		}
		void resize(size_t columns, size_t rows) {
			_storage.resize(rows * columns);
			_columns = columns;
		}

		size_t getColumns() const {
			return _columns;
		}
		size_t getRows() const {
			return _rows;
		}

	private:
		std::vector <Type> _storage;
		size_t _columns, _rows;
	};
}