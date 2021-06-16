#pragma once
//sf
#include <SFML/Graphics/RenderWindow.hpp> //RenderWindow

//std
#include <list> //list
#include <memory> //shared_ptr
#include <xutility> //find_if, swap, advance, prev

//atl
#include <atl/ui/Element.hpp> //ui::Element
#include <atl/abc/Renderer.hpp> //abc::IRenderer

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

		Iterator findByName(const std::string& _name) const {
			auto id = util::hash(_name);

			return std::find_if(m_layers.begin(), m_layers.end(), [id](const ui::Element& _it) { 
				return _it->get_id() == id;
			});
		}

		//insert item at the end of list
		Iterator add(ui::Element _what) {
			m_layers.push_back(_what);

			auto it = std::prev(m_layers.end());
			//(*it)->m_id = m_generator.allocate();

			return it;
		}
		//insert item in place of iterator
		Iterator add(ui::Element _what, Iterator _where) {
			auto it = m_layers.insert(_where, _what);
			return it;
		}

		//change order of drawing for current element
		Iterator changeOrder(Iterator _what, ptrdiff_t _offset) {
			auto copy = _what;
			std::advance(copy, _offset);

			std::swap(_what, copy);

			return _what;
		}

		Iterator remove(Iterator _where) {
			if (_where == m_layers.end())
				return m_layers.end();
			return m_layers.erase(_where);
		}

	protected:
		std::list <ui::Element> m_layers;
	};
}