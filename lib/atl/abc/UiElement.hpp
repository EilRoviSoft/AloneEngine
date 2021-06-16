#pragma once
//sf
#include <SFML/Graphics.hpp> //Drawable

//toml
#include <toml/value.hpp> //value

//std
#include <atomic> //atomic
#include <memory> //shared_ptr
#include <string> //string

//atl
#define TOML_LOADABLE
#include <atl/abc/Loadable.hpp> //abc::TomlLoadable
#include <atl/util/Functions.hpp> //util::hash

namespace atl::manager {
	class UiRenderer;
}

namespace atl::abc {
	class IUiElement : public sf::Drawable, public TomlLoadable {
		friend class manager::UiRenderer;
	public:
		std::atomic <bool> isVisible = true;

		size_t get_id() const {
			return _id;
		}

		bool virtual load(const toml::value& _data) {
			if (!_data.contains("name"))
				return false;

			set_id(_data.at("name").as_string());

			if (_data.contains("visible"))
				isVisible = _data.at("visible").as_boolean();

			return true;
		}

	protected:
		void set_id(const std::string& _name) {
			_id = util::hash(_name);
		}

	private:
		size_t _id;
	};

	using UiElement = std::shared_ptr <IUiElement>;
}