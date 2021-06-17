#pragma once
//std
#include <vector> //vector

namespace xtl {
	template <class Type>
	class Matrix {
	public:
		Matrix(size_t _columns = 0, size_t _rows = 0, const Type& _init = Type()) : 
			m_storage(_columns * _rows, _init), m_columnSize(_columns) {}

		Type& at(size_t _column, size_t _row) {
			return m_storage.at(_column * m_columnSize + _row);
		}
		const Type& at(size_t _column, size_t _row) const {
			return m_storage.at(_column * m_columnSize + _row);
		}

		void reserve(size_t _columns, size_t _rows) {
			m_storage.reserve(_rows * _columns);
			m_columnSize = _columns;
		}
		void resize(size_t _columns, size_t _rows) {
			m_storage.resize(_rows * _columns);
			m_columnSize = _columns;
		}

	protected:
		std::vector <Type> m_storage;
		size_t m_columnSize;
	};
}