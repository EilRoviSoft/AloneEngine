#pragma once
//std
#include <unordered_map> //unordered_map
#include <initializer_list> //intializer_list
#include <functional> //function
#include <string> //string

//atl
#include <atl/util/Functions.hpp> //util::hash

namespace atl::util {
	template <class Type>
	using WrapedTask = std::function <void(Type&)>;

	template <class Type>
	class Modifiers {
	public:
		Modifiers(const std::initializer_list <std::pair <std::string, WrapedTask <Type>>>& _init) {
			for (const auto& it : _init)
				m_tasks.insert({ hash(it.first), it.second });
		}

		void call(const std::string& _name, Type& _object) const {
			m_tasks.at(hash(_name))(_object);
		}

		void bind(const std::string& _name, const WrapedTask <Type>& _func) {
			m_tasks.insert({ hash(_name), _func });
		}

	protected:
		std::unordered_map <size_t, WrapedTask <Type>> m_tasks;
	};
}