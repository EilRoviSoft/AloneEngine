#pragma once
//std
#include <fstream> //ifstream, istream

//pugi (xml)
#include <pugixml/pugixml.hpp> //xml_document, xml_node

//atl
#include <atl/abc/Loadable.hpp> //abc::ILoadable

namespace atl::abc {
	class XmlLoadable : public ILoadable <const pugi::xml_node&> {
	public:
		bool loadFromStream(std::istream& in) override final {
			pugi::xml_document document;

			if (!document.load(in) || !document.child("main"))
				return false;

			return load(document.child("main"));
		}
	};
}