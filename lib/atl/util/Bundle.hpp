#pragma once
//std
#include <string> //string
#include <any> //any, any_cast, make_any
#include <unordered_map> //unordered_map

namespace atl::util {
	class Bundle {
	public:
		using KeyType = std::string;
		using ValueType = std::any;

		Bundle() {}
		~Bundle() {}

		template <class CastType>
		CastType& get(const KeyType& _key) {
			return std::any_cast <CastType>(m_storage.at(_key));
		}
		template <class ArgType>
		bool put(const KeyType& _key, const ArgType& _arg) {
			return m_storage.insert({ _key, std::make_any <ArgType>(_arg) }).second;
		}

	protected:
		std::unordered_map <KeyType, ValueType> m_storage;
	};
}