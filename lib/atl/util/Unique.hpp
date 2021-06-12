#pragma once
namespace atl::util {
	//TODO: casting value
	template <class T>
	class Unique {
	public:
		Unique(T* _value = nullptr) {
			_init(_value);
		}
		Unique(Unique&& _what) noexcept {
			_init(_what.m_value);
			_what.m_value = nullptr;
		}
		Unique(const Unique& _another) = delete;
		~Unique() {
			_remove_pointer();
		}

		static Unique&& create(T* _value) {
			return Unique(_value);
		}

		Unique& operator=(T* _value) {
			_remove_pointer();
			m_value = _value;
			return *this;
		}
		Unique& operator=(Unique&& _what) noexcept {
			_remove_pointer();
			m_value = _what.m_value;
			return *this;
		}
		Unique& operator=(const Unique& _another) = delete;

		T& get() const {
			return *m_value;
		}
		T& operator*() const {
			return get();
		}

		//replaces the managed object
		void set(T* _value) {
			m_value = _value;
		}

		//returns a pointer to the managed object and releases the ownership
		T* release() {
			T* result = m_value;
			m_value = nullptr;
			return result;
		}

		//checks whether value is stored
		operator bool() const {
			return m_value != nullptr;
		}

	protected:
		T* m_value;

	private:
		void _remove_pointer() {
			delete m_value;
		}
		void _init(T* _value) {
			m_value = _value;
		}
	};
}