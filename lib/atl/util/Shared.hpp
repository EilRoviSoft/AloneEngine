#pragma once
namespace atl::util {
	template <class T>
	class Shared;

	template <class T, class U>
	Shared <T> static_pointer_cast(const Shared <U>& _object) noexcept;
	template <class T, class U>
	Shared <T> dynamic_pointer_cast(const Shared <U>& _object) noexcept;
	template <class T, class U>
	Shared <T> const_pointer_cast(const Shared <U>& _object) noexcept;
	template <class T, class U>
	Shared <T> reinterpret_pointer_cast(const Shared <U>& _object) noexcept;

	//doesn't work with arrays, use instead container from STL
	template <class T>
	class Shared {
		template <class T, class U>
		friend Shared <T> static_pointer_cast(const Shared <U>& _object) noexcept;
		template <class T, class U>
		friend Shared <T> dynamic_pointer_cast(const Shared <U>& _object) noexcept;
		template <class T, class U>
		friend Shared <T> const_pointer_cast(const Shared <U>& _object) noexcept;
		template <class T, class U>
		friend Shared <T> reinterpret_pointer_cast(const Shared <U>& _object) noexcept;

	public:
		Shared(T* _value = nullptr, size_t* _count = new size_t(0)) {
			_init(_value, _count);
			(*m_count)++;
		}
		Shared(const Shared& _another) {
			_init(_another.m_value, _another.m_count);
			(*m_count)++;
		}
		Shared(Shared&& _what) noexcept {
			_init(_what.m_value, _what.m_count);
		}
		~Shared() {
			_remove_pointer();
		}

		Shared& operator=(const Shared& _another) {
			if (this == &_another)
				return *this;

			_remove_pointer();

			_init(_another.m_value, _another.m_count);

			if (m_value != nullptr)
				(*m_count)++;

			return *this;
		}
		Shared& operator=(Shared&& _what) noexcept {
			_remove_pointer();

			_init(_what.m_value, _what.m_count);

			_what.m_value = nullptr;
			_what.m_count = nullptr;

			return *this;
		}

		T* raw() const {
			return m_value;
		}
		T* operator->() const {
			return raw();
		}
		T& get() const {
			return *m_value;
		}
		T& operator*() const {
			return get();
		}

		void set(T* _value, size_t* _count = new size_t(1)) {
			_remove_pointer();
			_init(_value, _count);
		}
		void set(Shared <T>& _what) {
			_remove_pointer();
			_init(_what.m_value, _what.m_count);
		}

		//returns count of created copies
		size_t count() const {
			return *m_count;
		}

		//checks whether pointer is had single copy
		bool is_unique() const {
			return *m_count == 1;
		}

		//checks whether value is stored
		operator bool() const {
			return m_value != nullptr;
		}

		bool operator==(const Shared& _another) {
			return m_value == _another.m_value;
		}
		bool operator!=(const Shared& _another) {
			return m_value != _another.m_value;
		}

	protected:
		T* m_value;
		size_t* m_count;

	private:
		void _remove_pointer() {
			if (m_count == nullptr)
				return;

			(*m_count)--;

			if (*m_count == 0) {
				if (m_value != nullptr)
					delete m_value;
				delete m_count;
			}
		}
		void _init(T* _value, size_t* _count) {
			m_value = _value;
			m_count = _count;
		}
	};

	template <class T, class U>
	Shared <T> createShared(U* _value, size_t* _count = new size_t(0)) {
		return Shared <T>(_value, _count);
	}

	//TODO: const and reinterpreted cast
	template <class T, class U>
	Shared <T> static_pointer_cast(const Shared <U>& _object) noexcept {
		return Shared(static_cast <T*>(_object.m_value));
	}
	template <class T, class U>
	Shared <T> dynamic_pointer_cast(const Shared <U>& _object) noexcept {
		if (T* temp = dynamic_cast <T*>(_object.m_value))
			return Shared <T>(temp, _object.m_count);
		else
			return Shared <T>();
	}
	template<class T, class U>
	Shared <T> const_pointer_cast(const Shared<U>& _object) noexcept {
		return Shared <T>(const_cast <T*>(_object.m_value), _object.m_count);
	}
	template<class T, class U>
	Shared <T> reinterpret_pointer_cast(const Shared<U>& _object) noexcept {
		return Shared<T>(reinterpret_cast <T*>(_object.m_value), _object.m_count);
	}
}