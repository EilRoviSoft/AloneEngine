#pragma once
//std
#include <type_traits> //move
//#include <functional> //function

//atl
#include <atl/util/fail.hpp> //util::fail

namespace atl::util {
	template <class Type>
	//override operators: '->' and 'const Type&' for more flexible usage
	//also you can override operator 'Type&', but it's not recommended
	class IProperty {
	public:
		IProperty() {}
		IProperty(const Type& _value) : m_value(_value) {}
		IProperty(Type&& _value) : m_value(_value) {}

		virtual void set(const Type& _value) = 0;
		virtual void set(Type&& _value) = 0;

		virtual Type& get() = 0;
		virtual const Type& get() const = 0;

		Type&& extract() {
			return std::move(m_value);
		}

	protected:
		Type m_value;
	};

	template <class Type>
	class property : public IProperty <Type> {
	public:
		property() : IProperty <Type>() {}
		property(const Type& _value) : IProperty <Type>(_value) {}
		property(Type&& _value) : IProperty <Type>(_value) {}

		void set(const Type& _value) override {
			m_value = _value;
		}
		void set(Type&& _value) override {
			m_value = _value;
		}

		Type* operator->() {
			return &m_value;
		}

		Type& get() override {
			return m_value;
		}
		const Type& get() const override {
			return m_value;
		}

		operator const Type& () const {
			return m_value;
		}
	};

	template <class Type>
	class readonly : public property <Type> {
	public:
		readonly() : IProperty <Type>() {}
		readonly(const Type& _value) : property <Type>(_value) {}
		readonly(Type&& _value) : property <Type>(_value) {}

		void set(const Type& _value) override {
			static_assert(fail <bool>::value, "Don't use it!");
			//crutch, it's for remove warnings and errors
		}
		void set(Type&& _value) override {
			static_assert(fail <bool>::value, "Don't use it!");
			//crutch, it's for remove warnings and errors
		}

		Type& get() override {
			static_assert(fail <bool>::value, "Don't use it!");
			//crutch, it's for remove warnings and errors
			return m_value;
		}
		const Type& get() const override {
			static_assert(fail <bool>::value, "Don't use it!");
			//crutch, it's for remove warnings and errors
			return m_value;
		}
	};
}

using atl::util::property;
using atl::util::readonly;