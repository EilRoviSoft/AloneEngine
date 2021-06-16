#pragma once
//std
#include <type_traits> //move

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
		property(Type&& _value) noexcept : IProperty <Type>(_value) {}

		void set(const Type& _value) override {
			this->m_value = _value;
		}
		void set(Type&& _value) override {
			this->m_value = _value;
		}

		Type* operator->() {
			return &this->m_value;
		}

		Type& get() override {
			return this->m_value;
		}
		const Type& get() const override {
			return this->m_value;
		}

		operator const Type& () const {
			return this->m_value;
		}
	};
}

using atl::util::property;