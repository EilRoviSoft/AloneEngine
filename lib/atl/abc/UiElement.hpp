#pragma once
//pugi
#include <pugixml/pugixml.hpp> //xml_document

//std
#include <atomic> //atomic
#include <memory> //shared_ptr
#include <string> //string

//atl
#include <atl/abc/Renderable.hpp> //IRenderable
#include <atl/abc/XmlLoadable.hpp> //XmlLoadable
#include <atl/util/Functions.hpp> //hash

namespace atl {
	class IUiElement : public IRenderable, public XmlLoadable {
		friend class UiRenderer;
	public:
		static sf::Vector2f getCenter(sf::Vector2f position, sf::Vector2f size) {
			return sf::Vector2f(position.x - size.x / 2, position.y - size.y / 2);
		}

		std::atomic <bool> visible = true;

		size_t getId() const {
			return _id;
		}

		bool virtual load(const pugi::xml_node& data) {
			if (!data.attribute("name"))
				return false;

			setId(data.attribute("name").as_string());

			visible = data.attribute("visible").as_bool(true);

			return true;
		}

	protected:
		void setId(const std::string& another) {
			_id = hash(another);
		}

	private:
		size_t _id;
	};

	using UiElement = std::shared_ptr <IUiElement>;
}