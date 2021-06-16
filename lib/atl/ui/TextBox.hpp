#pragma once
//sf
#include <SFML/Graphics.hpp> //RenderTarget, RenderStates, Text, RectangleShape
#include <SFML/System.hpp> //String, Vector2f

//toml
#include <toml/value.hpp> //value

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

		virtual bool load(const toml::value& _data) override {
			if (!IElement::load(_data))
				return false;

			auto dataTextBox = _data.at("TextBox");
			//text
			{
				auto dataText = dataTextBox.at("text");

				if (!dataText.contains("string"))
					return false;

				text->setString(sf::String(dataText.at("string").as_string()));
				if (dataText.contains("size"))
					text->setCharacterSize(dataText.at("size").as_integer());

				//for top-left
				if (dataText.contains("position"))
					text->setPosition(util::loadVector2f(dataText.at("position")));
				else if (dataText.contains("center"))
					text->setPosition(util::calcPositionByCenter(util::loadVector2f(dataText.at("center")), text->getPosition()));
			}
			//box
			{
				auto dataBox = dataTextBox.at("box");

				if (dataBox.contains("size"))
					box->setSize(util::loadVector2f(dataBox.at("size")));
				if (dataBox.contains("position"))
					box->setPosition(util::loadVector2f(dataBox.at("position")));
				if (dataBox.contains("color-inline"))
					box->setFillColor(util::loadColor(dataBox.at("color-inline")));
				if (dataBox.contains("color-outline"))
					box->setOutlineColor(util::loadColor(dataBox.at("color-outline")));
			}

			if (dataTextBox.contains("mods")) {
				auto temp = dataTextBox.at("mods").as_array();

				for (const auto& it : temp)
					TextBox::mods.call(it.as_string(), *this);
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