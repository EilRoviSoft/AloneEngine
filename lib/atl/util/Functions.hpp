#pragma once
namespace atl::util {
	template <class Type>
	size_t hash(Type _what) {
		return std::hash <Type> {}(_what);
	}

#ifdef TOML_LOADABLE
#ifdef SFML_COLOR_HPP
	sf::Color loadColor(const toml::value& _data) {
		if (_data.is_table())
			return sf::Color(_data.at("r").as_integer(), _data.at("g").as_integer(), _data.at("b").as_integer(),
				_data.contains("a") ? _data.at("a").as_integer() : 255);
		else
			return sf::Color(_data.as_integer());
	}
#endif
#ifdef SFML_VECTOR2_HPP
	sf::Vector2f loadVector2f(const toml::value& _data) {
		if (_data.is_table())
			return sf::Vector2f(_data.at("x").as_floating(), _data.at("y").as_floating());
		else
			return sf::Vector2f(_data[0].as_floating(), _data[1].as_floating());
	}
#endif
#endif
}