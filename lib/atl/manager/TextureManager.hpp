#pragma once
//std
#include <string> //string
//#include <iostream> //cerr

//sfml
#include <SFML/Graphics/Texture.hpp> //Texture

//toml
#include <toml/value.hpp> //value

//atl
#include <atl/abc/Manager.hpp> //abc::IManager
#include <atl/util/Functions.hpp> //util::hash

namespace atl::manager {
	class TextureManager : public abc::IManager <sf::Texture> {
	protected:
		void loadItem(const std::string& folder, const toml::value& data) override {
			size_t key = util::hash(data.as_string());
			m_content.insert({ key, sf::Texture() });

			auto it = m_content.find(key);
			if (it != m_content.end())
				it->second.loadFromFile(folder + data.as_string().str);
		}

	public:
		TextureManager() {}
		TextureManager(const std::string& filename) {
			loadFromFile(filename);
		}
	};
}