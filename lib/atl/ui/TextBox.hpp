#pragma once
//sf
#include <SFML/Graphics.hpp> //RenderTarget, RenderStates, Text, RectangleShape
#include <SFML/System.hpp> //String, Vector2f

//toml
#include <toml/value.hpp> //value

//atl
#include <atl/util/readonly.hpp> //readonly
#include <atl/ui/Element.hpp> //IElement
//#include <atl/util/Modifiers.hpp> //Modifiers

namespace atl::ui {
	class TextBox : public IElement {
	public:
		//static const util::Modifiers mods;

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

		virtual bool load(const toml::value& _data) override {
			IElement::load(_data);

			auto dataTextBox = _data.at("TextBox");
			//text
			{
				auto dataText = dataTextBox.at("text");
				text->setString(sf::String(_data.at("string").as_string()));
				if (_data.contains("size"))
					text->setCharacterSize(_data.at("size").as_integer());
			}
			{
				auto dataBox = dataTextBox.at("box");

			}
		}

	protected:
		virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			if (!isVisible) return void();

			_target.draw(box, _states);
			_target.draw(text, _states);
		}
	};

	/*const util::Modifiers TextBox::mods = {
		{}
	};*/
}