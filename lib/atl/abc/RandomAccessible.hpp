#pragma once
namespace atl {
	template <class Type>
	class IRandomAccessible {
	public:
		virtual Type& at(size_t where) = 0;
		virtual const Type& at(size_t where) const = 0;
	};
}