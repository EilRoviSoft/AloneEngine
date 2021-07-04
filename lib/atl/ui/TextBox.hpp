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
		TextBox();
		TextBox(const sf::Text& text, const sf::RectangleShape& box);

		const sf::Text& getText() const;
		const sf::RectangleShape& getBox() const;

		void setFont(const sf::Font& font);
		
		void wrapText(float padding = 5.f);

		virtual bool load(const pugi::xml_node& data) override;

	protected:
		sf::Text& getText();
		void setText(const sf::Text& text);

		sf::RectangleShape& getBox();
		void setBox(const sf::RectangleShape& box);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		sf::Text _text;
		sf::RectangleShape _box;
	};
}