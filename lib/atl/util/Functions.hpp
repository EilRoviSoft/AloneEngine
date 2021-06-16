#pragma once
namespace atl::util {
	template <class Type>
	size_t hash(Type _what) {
		return std::hash <Type> {}(_what);
	}

#ifdef XML_LOADABLE
#ifdef SFML_COLOR_HPP
	sf::Color loadColor(const pugi::xml_node& _data) {
		if (_data.attribute("value"))
			return sf::Color(_data.attribute("value").as_uint());
		else
			return sf::Color(_data.attribute("r").as_uint(0), _data.attribute("g").as_uint(0), _data.attribute("b").as_uint(0),
				_data.attribute("a").as_uint(255));
	}
#endif
#ifdef SFML_VECTOR2_HPP
	sf::Vector2f loadVector2f(const pugi::xml_node& _data) {
		return sf::Vector2f(_data.attribute("x").as_float(), _data.attribute("y").as_float());
	}
#endif
#endif
}