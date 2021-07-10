#include "TextBox.hpp"

atl::TextBox::TextBox() : IUiElement() {}
atl::TextBox::TextBox(const sf::Text& text, const sf::RectangleShape& box) :
	_text(text), _box(box), IUiElement() {}

const sf::Text& atl::TextBox::getText() const {
	return _text;
}
const sf::RectangleShape& atl::TextBox::getBox() const {
	return _box;
}

void atl::TextBox::setFont(const sf::Font& font) {
	_text.setFont(font);
}

void atl::TextBox::wrapText(float padding) {
	auto rect = _text.getGlobalBounds();
	auto position = _text.getPosition();
	float dx = rect.left - position.x, dy = rect.top - position.y;

	_box.setSize(sf::Vector2f(rect.width + dx + padding * 2, rect.height + dy + padding * 2));
	_box.setPosition(sf::Vector2f(position.x - padding, position.y - padding));
}

bool atl::TextBox::load(const pugi::xml_node& data) {
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

sf::Text& atl::TextBox::getText() {
	return _text;
}
void atl::TextBox::setText(const sf::Text& text) {
	_text = text;
}

sf::RectangleShape& atl::TextBox::getBox() {
	return _box;
}
void atl::TextBox::setBox(const sf::RectangleShape& box) {
	_box = box;
}

void atl::TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (!visible) return void();

	target.draw(_box, states);
	target.draw(_text, states);
}

const atl::Modifiers <atl::TextBox> atl::TextBox::mods = {
		{ "wrap", [](TextBox& tb) { return tb.wrapText(); } }
};