#pragma once
//std
#include <string> //std::string
#include <unordered_map> //std::unoredered_map

//atl
#define TOML_LOADABLE
#include <atl/abc/Loadable.hpp> //sf::TomlLoadable

namespace atl::abc {
	template <class ValueType>
	class IManager : public abc::TomlLoadable {
	protected:
		std::unordered_map <size_t, ValueType> m_content;

		virtual void loadItem(const std::string& _folder, const toml::value& _it) = 0;

	public:
		bool load(const toml::value& _data) override {
			if (!_data.contains("path") || !_data.contains("files"))
				return false;

			std::string path = _data.at("path").as_string();

			for (auto it : _data.at("files").as_array())
				this->loadItem(path, it);

			return true;
		}

		ValueType& at(const std::string& _key) {
			return this->m_content.at(std::hash <std::string>{} (_key));
		}
		const ValueType& at(const std::string& _key) const {
			return this->m_content.at(std::hash <std::string>{} (_key));
		}
	};
}