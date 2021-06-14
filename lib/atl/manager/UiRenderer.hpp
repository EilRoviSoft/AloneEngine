#pragma once
//sf
#include <SFML/Graphics/RenderWindow.hpp> //RenderWindow

//std
#include <list> //list
#include <memory> //shared_ptr
#include <algorithm> //find_if

//atl
#include <atl/ui/Element.hpp> //Element
#include <atl/abc/Renderer.hpp> //IRenderer

namespace atl::manager {
	//shared or unique based?
	//now is shared based
	class UiRenderer : public abc::IRenderer {
	public:
		using Iterator = std::list <ui::Element>::const_iterator;

		void render(sf::RenderWindow& _window) const final override {
			for (const auto& it : m_layers)
				_window.draw(*it);
		}

		Iterator findById(size_t _id) const {
			return std::find_if(m_layers.begin(), m_layers.end(), [_id](const ui::Element& _it) { 
				return _it->id() == _id; 
			});
		}

		//insert item at the end of list
		Iterator add(ui::Element _what) {
			return m_layers.insert(m_layers.end(), _what);
		}
		//insert item in place of iterator
		Iterator add(ui::Element _what, Iterator _where) {
			return m_layers.insert(_where, _what);
		}

		Iterator remove(Iterator _where) {
			return m_layers.erase(_where);
		}

	protected:
		std::list <ui::Element> m_layers;
	};
}