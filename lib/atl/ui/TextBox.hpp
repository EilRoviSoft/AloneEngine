#pragma once
//std
#include <string> //string

//sf
#include <SFML/Graphics.hpp> //RenderTarget, RenderStates, Text, RectangleShape
#include <SFML/System.hpp> //String, Vector2f

//pugi
#include <pugixml/pugixml.hpp> //xml_node

//atl
#include <atl/util/readonly.hpp> //util::readonly
#include <atl/ui/Element.hpp> //ui::IElement
#include <atl/util/Modifiers.hpp> //util::Modifiers
#include <atl/util/Functions.hpp> //util::loadColor, util::loadVector2f

namespace atl::ui {
	class TextBox : public IElement {
		static const util::Modifiers <TextBox> mods;
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

		virtual bool load(const pugi::xml_node& _data) override {
			if (!IUiElement::load(_data)) return false;

			if (!_data.child("TextBox")) return false;
			auto dataTextBox = _data.child("TextBox");
			//text
			{
				if (!dataTextBox.child("Text")) return false;
				auto dataText = dataTextBox.child("Text");

				text->setString(sf::String(dataText.attribute("string").as_string()));
				text->setCharacterSize(dataText.attribute("size").as_uint(30));

				if (dataText.attribute("align").as_string("top-left") == "center") {
					auto bounds = text->getLocalBounds();

					text->setPosition(dataText.attribute("x").as_float() - bounds.width / 2, dataText.attribute("y").as_float() - bounds.height / 2);
				} else
					//if align top-left or another, which now is unsupported
					text->setPosition(dataText.attribute("x").as_float(), dataText.attribute("y").as_float());
			}

			//box
			{
				if (!dataTextBox.child("Box")) return false;
				auto dataBox = dataTextBox.child("Box");

				box->setSize(sf::Vector2f(dataBox.attribute("width").as_float(), dataBox.attribute("height").as_float()));
				box->setPosition(dataBox.attribute("x").as_float(), dataBox.attribute("y").as_float());
				box->setFillColor(sf::Color(dataBox.attribute("inline-color").as_ullong()));
				box->setOutlineColor(sf::Color(dataBox.attribute("outline-color").as_ullong()));
			}

			for (const auto& it : dataTextBox.child("Mods").attributes())
				TextBox::mods.call(it.as_string(), *this);

			return true;
		}

	protected:
		virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override {
			if (!isVisible) return void();

			_target.draw(box, _states);
			_target.draw(text, _states);
		}
	};

	const util::Modifiers <TextBox> TextBox::mods = {
		{ "wrap", [](TextBox& _tb) { return _tb.wrapText(); } }
	};
}