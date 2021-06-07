#pragma once
//std
#include <string> //string

//sfml
#include <SFML/Graphics/Texture.hpp> //Texture

//toml
#include <toml/include.hpp> //value

//atl
#include <atl/abc/Manager.hpp> //abc::IManager
#include <atl/util/Functions.hpp> //util::hash

namespace atl::manager {
	class TextureManager : public abc::IManager <sf::Texture> {
	protected:
		void loadItem(const std::string& _folder, const toml::value& _it) override {
			this->m_content.insert({ util::hash <std::string>{} ((std::string) _it.as_string()), sf::Texture() });

			auto it = this->m_content.find(std::hash <std::string>{} ((std::string) _it.as_string()));

			if (it != this->m_content.end())
				it->second.loadFromFile(_folder + (std::string) _it.as_string());
		}

	public:
		TextureManager() : abc::IManager <sf::Texture>() {}
		TextureManager(const std::string& _filename) {
			this->loadFromFile(_filename);
		}
	};
}