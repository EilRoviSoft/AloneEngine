#pragma once
//std
#include <unordered_map> //unordered_map
#include <initializer_list> //intializer_list
#include <functional> //function
#include <string> //string

//atl
#include <atl/util/Functions.hpp> //hash

namespace atl {
	template <class Type>
	using WrapedTask = std::function <void(Type&)>;

	template <class Type>
	class Modifiers {
	public:
		Modifiers(const std::initializer_list <std::pair <std::string, WrapedTask <Type>>>& init) {
			for (const auto& it : init)
				m_tasks.insert({ hash(it.first), it.second });
		}

		void call(const std::string& name, Type& object) const {
			auto key = hash(name);

			if (!m_tasks.contains(key))
				return void();

			m_tasks.at(key)(object);
		}

		void bind(const std::string& name, const WrapedTask <Type>& task) {
			m_tasks.insert({ hash(name), task });
		}

	protected:
		std::unordered_map <size_t, WrapedTask <Type>> m_tasks;
	};
}