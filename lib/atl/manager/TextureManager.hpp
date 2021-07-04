#pragma once
//std
#include <string> //string

//sfml
#include <SFML/Graphics/Texture.hpp> //Texture

//atl
#include <atl/abc/Manager.hpp> //IManager, toml::value
#include <atl/util/Functions.hpp> //hash

namespace atl {
	class TextureManager : public IManager <sf::Texture> {
	public:
		TextureManager() {}
		TextureManager(const std::string& filename) {
			loadFromFile(filename);
		}

	protected:
		void loadItem(const std::string& folder, const toml::value& data) override {
			size_t key = util::hash <std::string>(data.as_string());
			m_content.insert({ key, sf::Texture() });

			auto it = m_content.find(key);
			if (it != m_content.end())
				it->second.loadFromFile(folder + data.as_string().str);
		}
	};
}