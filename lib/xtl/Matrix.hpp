#pragma once
//std
#include <vector> //vector

namespace xtl {
	template <class Type>
	class Matrix {
	public:
		Matrix(size_t columns = 0, size_t rows = 0, const Type& init = Type()) : 
			m_storage(columns * rows, init), m_columnSize(columns) {}

		Type& at(size_t column, size_t row) {
			return m_storage.at(column * m_columnSize + row);
		}
		const Type& at(size_t column, size_t ow) const {
			return m_storage.at(column * m_columnSize + ow);
		}

		void reserve(size_t columns, size_t rows) {
			m_storage.reserve(rows * columns);
			m_columnSize = columns;
		}
		void resize(size_t columns, size_t rows) {
			m_storage.resize(rows * columns);
			m_columnSize = columns;
		}

	protected:
		std::vector <Type> m_storage;
		size_t m_columnSize;
	};
}