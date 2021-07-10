#pragma once
//sf
#include <SFML/Graphics/RenderWindow.hpp> //RenderWindow

//std
#include <list> //list
#include <memory> //shared_ptr
#include <xutility> //find_if, swap, advance, prev

//atl
#include <atl/abc/UiElement.hpp> //UiElement
#include <atl/abc/Renderer.hpp> //IRenderer

namespace atl {
	//shared or unique based?
	//now is shared based

	//TODO: now every drawing
	class UiRenderer : public IRenderer {
	public:
		using Iterator = std::list <UiElement>::const_iterator;

		void prerender(GameWindow& target, sf::RenderStates states) const final override;
		void render(GameWindow& target, sf::RenderStates states) const final override;

		Iterator findByName(const std::string& name) const;

		//insert item at the end of list
		Iterator add(UiElement what);
		//insert item in place of iterator
		Iterator add(UiElement what, Iterator where);

		//change order of drawing for current element
		Iterator changeOrder(Iterator what, ptrdiff_t offset);

		Iterator remove(Iterator where);

	private:
		std::list <UiElement> _layers;
		std::list <UiElement*> _onUpdateElements;
	};
}