#pragma once
//sf
#include <SFML/Graphics.hpp> //RenderTarget, RenderStates, Text, RectangleShape
#include <SFML/System/Vector2.hpp> //Vector2f

//atl
#include <atl/util/readonly.hpp> //readonly
#include <atl/ui/Element.hpp> //IElement

namespace atl::ui {
	class TextBox : public IElement {
	public:
		TextBox() : IElement() {}
		TextBox(const sf::Text& _text, const sf::RectangleShape& _back) :
			text(_text), box(_back), IElement() {}

		readonly <sf::Text> text;
		readonly <sf::RectangleShape> box;
		
		void wrapText(float _padding = 5.f) {
			auto rect = text->getGlobalBounds();
			auto position = text->getPosition();
			float dx = rect.left - position.x, dy = rect.top - position.y;

			box->setSize(sf::Vector2f(rect.width + dx + _padding * 2, rect.height + dy + _padding * 2));
			box->setPosition(sf::Vector2f(position.x - _padding, position.y - _padding));
		}

	protected:
		virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			if (!isVisible) return void();

			_target.draw(box, _states);
			_target.draw(text, _states);
		}
	};
}