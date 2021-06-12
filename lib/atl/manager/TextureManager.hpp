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
		void loadItem(const std::string& _folder, const toml::value& _it) override {
			size_t key = util::hash(_it.as_string());
			this->m_content.insert({ key, sf::Texture() });

			auto it = this->m_content.find(key);
			if (it != this->m_content.end())
				it->second.loadFromFile(_folder + _it.as_string().str);
		}

	public:
		TextureManager() {}
		TextureManager(const std::string& _filename) {
			this->loadFromFile(_filename);
		}
	};
}