#pragma once
//std
#include <vector> //vector

namespace atl {
	//TODO: horizontal and vertical iterators and iterable_regions
	template <class Type>
	class Matrix {
	public:
		Matrix(size_t rows = 0, size_t cols = 0) {
			resize(rows, cols);
		}

		Type& at(size_t i, size_t j) {
			return _data.at(i * _cols + j);
		}
		const Type& at(size_t i, size_t j) const {
			return _data.at(i * _cols + j);
		}

		void resize(size_t rows, size_t cols) {
			_rows = rows;
			_cols = cols;

			_data.resize(_rows * _cols);
		}

		size_t rows() const {
			return _rows;
		}
		size_t cols() const {
			return _cols;
		}
		size_t size() const {
			return _rows * _cols;
		}

	protected:
		Type& at(size_t abs) {
			return _data.at(abs);
		}
		const Type& at(size_t abs) const {
			return _data.at(abs);
		}

		/*void from(const std::vector <Type>& vector) {
			_data = vector;
		}
		void from(std::vector <Type>&& vector) {
			_data = vector;
		}
		template <class InputIt>
		void from(InputIt first, InputIt last) {
			_data.assign(first, last);
		}*/

	private:
		size_t _rows, _cols;
		std::vector <Type> _data;
	};
}