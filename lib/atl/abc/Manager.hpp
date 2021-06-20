#pragma once
//std
#include <string> //string
#include <unordered_map> //unoredered_map

//atl
#include <atl/abc/TomlLoadable.hpp> //TomlLoadable, toml::value
#include <atl/util/Functions.hpp> //util::hash

namespace atl::abc {
	template <class ValueType>
	class IManager : public abc::TomlLoadable {
	public:
		bool load(const toml::value& data) override {
			if (!data.contains("path") || !data.contains("files"))
				return false;

			std::string path = data.at("path").as_string();

			for (auto it : data.at("files").as_array())
				loadItem(path, it);

			return true;
		}

		ValueType& at(const std::string& key) {
			return m_content.at(util::hash(key));
		}
		const ValueType& at(const std::string& key) const {
			return m_content.at(util::hash(key));
		}

	protected:
		std::unordered_map <size_t, ValueType> m_content;

		virtual void loadItem(const std::string& folder, const toml::value& data) = 0;
	};
}