#pragma once
//sf
#include <SFML/Graphics.hpp> //RenderTarget, RenderStates, Text, RectangleShape
#include <SFML/System/Vector2.hpp> //Vector2f

//atl
#include <atl/util/property.hpp> //readonly
#include <atl/ui/Element.hpp> //IElement

namespace atl::ui {
	class TextBox : public IElement {
	public:
		TextBox() : IElement() {}
		TextBox(const sf::Text& _text, const sf::RectangleShape& _back) :
			text(_text), box(_back), IElement() {}

		readonly <sf::Text> text;
		readonly <sf::RectangleShape> box;
		
		//TODO
		void wrapText() {
			
		}

	protected:
		virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			if (!isVisible) return void();

			_target.draw(box, _states);
			_target.draw(text, _states);
		}
	};
}