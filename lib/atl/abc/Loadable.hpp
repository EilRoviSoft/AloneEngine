#pragma once
#ifdef TOML_LOADABLE
//toml
#include <toml/include.hpp> //value
#endif
#ifdef JSON_LOADABLE
//nlohmann (json)
#include <nlohmann/json.hpp> //json
#endif
#ifdef XML_LOADABLE
//pugi (xml)
#include <pugixml/pugixml.hpp> //xml_document, xml_node
#endif

//std
#include <string> //string
#include <istream> //istream
#include <fstream> //ifstream

namespace atl::abc {
	template <class UserDataType>
	class ILoadable {
	public:
		using Type = UserDataType;

		virtual bool loadFromFile(const std::string& _filename) {
			std::ifstream file(_filename);
			auto result = loadFromStream(file);
			file.close();

			return result;
		}
		virtual bool loadFromStream(std::istream& _in) = 0;
		//You have to override it yourself
		virtual bool load(const UserDataType& _data) = 0;
	};

#ifdef TOML_LOADABLE
	class TomlLoadable : public ILoadable <toml::value> {
	public:
		//it's crutch, because of Windows weird reading toml file
		bool loadFromFile(const std::string& _filename) override final {
			std::ifstream file(_filename, std::ios_base::binary);
			auto result = loadFromStream(file);
			file.close();

			return result;
		}
		bool loadFromStream(std::istream& _in) override final {
			return load(toml::parse(_in));
		}
	};
#endif
#ifdef JSON_LOADABLE
	class JsonLoadable : public ILoadable <nlohmann::json> {
	public:
		bool loadFromStream(std::istream& _in) override final {
			return load(nlohmann::json::parse(_in));
		}
	};
#endif
#ifdef XML_LOADABLE
	class XmlLoadable : public ILoadable <pugi::xml_node> {
	public:
		bool loadFromStream(std::istream& _in) override final {
			pugi::xml_document document;

			if (!document.load(_in) || !document.child("main"))
				return false;
			
			return load(document.child("main"));
		}
	};
#endif
}