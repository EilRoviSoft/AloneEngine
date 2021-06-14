#pragma once
//sf
#include <SFML/Graphics.hpp> //Drawable

//std
#include <atomic>

namespace atl::ui {
	class IElement : public sf::Drawable {
	public:
		std::atomic <bool> isVisible = true;

		size_t id() const {
			return m_id;
		}
		
	protected:
		IElement() {}
		IElement(size_t _id) : m_id(_id) {}
		
		size_t& id() {
			return m_id;
		}

		size_t m_id;
	};
}