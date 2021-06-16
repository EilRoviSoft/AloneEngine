#pragma once
namespace atl::util {
	template <class Type>
	class readonly {
	public:
		readonly(const Type& _value = Type()) : m_value(_value) {}
		readonly(Type&& _value) noexcept : m_value(_value) {}

		Type* operator->() {
			return &this->m_value;
		}

		operator const Type& () const {
			return m_value;
		}
		operator Type& () {
			return m_value;
		}

	protected:
		Type m_value;

		//removes CopyAssigment and MoveAssigment

		readonly& operator=(const readonly&) = delete;
		readonly& operator=(readonly&&) = delete;
	};
}

using atl::util::readonly;