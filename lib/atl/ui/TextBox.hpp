#pragma once
//std
#include <string> //string

//sf
#include <SFML/Graphics.hpp> //RenderTarget, RenderStates, Text, RectangleShape
#include <SFML/System.hpp> //String, Vector2f

//pugi
#include <pugixml/pugixml.hpp> //xml_node

//atl
#include <atl/abc/UiElement.hpp> //UiElement
#include <atl/util/Modifiers.hpp> //Modifiers

namespace atl {
	template <class WhatType>
	class Editor;

	class TextBox : public IUiElement {
		friend Editor <TextBox>;
		static const Modifiers <TextBox> mods;
	public:
		TextBox() : IUiElement() {}
		TextBox(const sf::Text& text, const sf::RectangleShape& box) :
			_text(text), _box(box), IUiElement() {}

		const sf::Text& getText() const {
			return _text;
		}
		const sf::RectangleShape& getBox() const {
			return _box;
		}

		void setFont(const sf::Font& font) {
			_text.setFont(font);
		}
		
		void wrapText(float padding = 5.f) {
			auto rect = _text.getGlobalBounds();
			auto position = _text.getPosition();
			float dx = rect.left - position.x, dy = rect.top - position.y;

			_box.setSize(sf::Vector2f(rect.width + dx + padding * 2, rect.height + dy + padding * 2));
			_box.setPosition(sf::Vector2f(position.x - padding, position.y - padding));
		}

		virtual bool load(const pugi::xml_node& data) override {
			if (!IUiElement::load(data)) return false;

			if (!data.child("TextBox")) return false;
			auto dataTextBox = data.child("TextBox");
			//text
			{
				if (!dataTextBox.child("Text")) return false;
				auto dataText = dataTextBox.child("Text");

				_text.setString(sf::String(dataText.attribute("string").as_string()));
				_text.setCharacterSize(dataText.attribute("size").as_uint(30));

				if (dataText.attribute("align").as_string("top-left") == "center") {
					auto bounds = _text.getLocalBounds();

					_text.setPosition(dataText.attribute("x").as_float() - bounds.width / 2, dataText.attribute("y").as_float() - bounds.height / 2);
				} else
					//if align top-left or another, which now is unsupported
					_text.setPosition(dataText.attribute("x").as_float(), dataText.attribute("y").as_float());
			}

			//box
			{
				if (!dataTextBox.child("Box")) return false;
				auto dataBox = dataTextBox.child("Box");

				_box.setSize(sf::Vector2f(dataBox.attribute("width").as_float(), dataBox.attribute("height").as_float()));
				_box.setPosition(dataBox.attribute("x").as_float(), dataBox.attribute("y").as_float());
				_box.setFillColor(sf::Color(dataBox.attribute("inline-color").as_ullong()));
				_box.setOutlineColor(sf::Color(dataBox.attribute("outline-color").as_ullong()));
			}

			for (const auto& it : dataTextBox.child("Mods").attributes())
				TextBox::mods.call(it.as_string(), *this);

			return true;
		}

	protected:
		sf::Text& getText() {
			return _text;
		}
		sf::RectangleShape& getBox() {
			return _box;
		}

		void setText(const sf::Text& text) {
			_text = text;
		}
		void setBox(const sf::RectangleShape& box) {
			_box = box;
		}

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
			if (!visible) return void();

			target.draw(_box, states);
			target.draw(_text, states);
		}

	private:
		sf::Text _text;
		sf::RectangleShape _box;
	};

	const Modifiers <TextBox> TextBox::mods = {
		{ "wrap", [](TextBox& tb) { return tb.wrapText(); } }
	};
}