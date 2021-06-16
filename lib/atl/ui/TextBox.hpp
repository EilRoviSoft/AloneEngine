#pragma once
//sf
#include <SFML/Graphics.hpp> //RenderTarget, RenderStates, Text, RectangleShape
#include <SFML/System.hpp> //String, Vector2f

//pugi
#include <pugixml/pugixml.hpp> //xml_node

//atl
#include <atl/util/readonly.hpp> //util::readonly
#include <atl/ui/Element.hpp> //ui::IElement
#include <atl/util/Modifiers.hpp> //util::Modifiers
#include <atl/util/Functions.hpp> //util::loadColor, util::loadVector2f, calcPositionByCenter
//#include <atl/game_tools/Core.hpp> //core

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
				if (!dataTextBox.child("text")) return false;
				auto dataText = dataTextBox.child("text");

				if (!dataText.attribute("string"))
					return false;

				text->setString(sf::String(dataText.attribute("string").as_string()));
				text->setCharacterSize(dataText.attribute("size").as_uint(30));

				if (dataText.child("center")) {
					auto bounds = text->getLocalBounds();

					text->setPosition(abc::IUiElement::calcPositionByCenter(
						util::loadVector2f(dataText.child("center")), sf::Vector2f(bounds.width, bounds.height)));
				} else
					text->setPosition(util::loadVector2f(dataText.child("position")));
			}

			//box
			{
				if (!dataTextBox.child("box")) return false;
				auto dataBox = dataTextBox.child("box");
				
				box->setSize(util::loadVector2f(dataBox.child("size")));
				box->setPosition(util::loadVector2f(dataBox.child("position")));
				box->setFillColor(util::loadColor(dataBox.child("color-inline")));
				box->setOutlineColor(util::loadColor(dataBox.child("color-outline")));
			}

			if (dataTextBox.child("mods")) {
				for (const auto& it : dataTextBox.child("mods"))
					TextBox::mods.call(it.attribute("content").as_string(), *this);
			}

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