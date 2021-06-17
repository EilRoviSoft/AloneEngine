#pragma once
//sf
#include <SFML/Graphics.hpp> //Drawable

//pugi
#include <pugixml/pugixml.hpp> //xml_document

//std
#include <atomic> //atomic
#include <memory> //shared_ptr
#include <string> //string

//atl
#define XML_LOADABLE
#include <atl/abc/Loadable.hpp> //abc::XmlLoadable
#include <atl/util/Functions.hpp> //util::hash

namespace atl::manager {
	class UiRenderer;
}

namespace atl::abc {
	class IUiElement : public sf::Drawable, public XmlLoadable {
		friend class manager::UiRenderer;
	public:
		static sf::Vector2f getCenter(sf::Vector2f _position, sf::Vector2f _size) {
			return sf::Vector2f(_position.x - _size.x / 2, _position.y - _size.y / 2);
		}

		std::atomic <bool> isVisible = true;

		size_t get_id() const {
			return _id;
		}

		bool virtual load(const pugi::xml_node& _data) {
			if (!_data.attribute("name"))
				return false;

			set_id(_data.attribute("name").as_string());

			isVisible = _data.attribute("visible").as_bool(true);

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