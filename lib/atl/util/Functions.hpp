#pragma once
namespace atl::util {
	template <class Type>
	size_t hash(Type _what) {
		return std::hash <Type> {}(_what);
	}

#ifdef TOML_LOADABLE
#ifdef SFML_COLOR_HPP
	sf::Color loadColor(const toml::value& _data) {
		if (_data.is_table()) {
			auto temp = _data.as_table();

			return sf::Color(temp.at("a").as_integer(), temp.at("g").as_integer(), temp.at("b").as_integer(),
				temp.contains("a") ? temp.at("a").as_integer() : 255);
		} else if (_data.is_array()) {
			auto temp = _data.as_array();

			return sf::Color(temp.at(0).as_integer(), temp.at(1).as_integer(), temp.at(2).as_integer(),
				temp.size() == 4 ? temp.at(3).as_integer() : 255);
		} else
			return sf::Color(_data.as_integer());
	}
#endif
#ifdef SFML_VECTOR2_HPP
	sf::Vector2f loadVector2f(const toml::value& _data) {
		if (_data.is_table()) {
			auto temp = _data.as_table();

			return sf::Vector2f(temp.at("x").as_floating(), temp.at("y").as_floating());
		} else {
			auto temp = _data.as_array();

			return sf::Vector2f(temp.at(0).as_floating(), temp.at(1).as_floating());
		}
	}
#endif
#endif

#ifdef SFML_VECTOR2_HPP
	//_position is central
	sf::Vector2f calcPositionByCenter(sf::Vector2f _position, sf::Vector2f _size) {
		return sf::Vector2f(_position.x - _size.x / 2, _position.y - _size.y / 2);
	}
#endif
}