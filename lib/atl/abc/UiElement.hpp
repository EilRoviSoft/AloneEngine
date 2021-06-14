#pragma once
//sf
#include <SFML/Graphics.hpp> //Drawable

//std
#include <atomic> //atomic
#include <memory> //shared_ptr

namespace atl::abc {
	class IUiElement : public sf::Drawable {
	public:
		std::atomic <bool> isVisible = true;

		const size_t& id() const {
			return m_id;
		}
		
	protected:
		IUiElement() {}
		IUiElement(size_t _id) : m_id(_id) {}



		size_t m_id;
	};

	using UiElement = std::shared_ptr <IUiElement>;
}