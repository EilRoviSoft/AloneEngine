#pragma once
//std
#include <cstdint> //uint8_t
#include <memory> //shared_ptr

//xtl
#include <xtl/Matrix.hpp> //Matrix

namespace atl::game {
	using id_t = uint8_t;

	class ITile {
	public:
		const id_t& get_id() const {
			return _id;
		}

	protected:
		void set_id(id_t _value) {
			_id = _value;
		}

	private:
		id_t _id;
	};
	using Tile = std::shared_ptr <ITile>;

	class Layer {
	public:


		void setTile(ITile* _value, size_t _x, size_t _y) {
			m_storage.at(_y, _x).reset(_value);
		}

		Tile& getTile(size_t _x, size_t _y) {
			return m_storage.at(_y, _x);
		}
		const Tile& getTile(size_t _x, size_t _y) const {
			return m_storage.at(_y, _x);
		}

	private:
		xtl::Matrix <Tile> m_storage;
	};
}