#pragma once
//std
#include <unordered_map> //unordered_map
#include <initializer_list> //intializer_list
#include <functional> //function
#include <string> //string

//atl
#include <atl/util/Functions.hpp> //util::hash

namespace atl::util {
	//now working only with void(void)

	using Task = std::function <void(void)>;

	class Modifiers {
	public:
		Modifiers(const std::initializer_list <std::pair <size_t, Task>>& _init) {
			for (const auto& it : _init)
				m_tasks.insert(it);
		}

		void call(const std::string& _name) const {
			m_tasks.at(hash(_name))();
		}

		void bind(const std::string& _name, Task _func) {
			m_tasks.insert({ hash(_name), _func });
		}

	protected:
		std::unordered_map <size_t, Task> m_tasks;
	};
}