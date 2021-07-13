#pragma once
namespace uxl {
	template <class Type>
	class RequestQueue {
	public:
		struct Node {
			Node(Type value, Node* next = nullptr) : value(value), next(next) {}

			Type value;
			Node* next;
		};
		class Iterator {
		public:
			Iterator(Node* position) : _position(position) {}

			Iterator operator++(int) {
				auto result = *this;
				_position = _position->next;

				return result;
			}
			const Iterator operator++() {
				_position = _position->next;
				return *this;
			}

			Type operator*() {
				return _position->value;
			}
			
			bool operator==(const Iterator& another) const {
				return _position == another._position;
			}
			bool operator!=(const Iterator& another) const {
				return _position != another._position;
			}

		private:
			Node* _position;
		};

		Iterator begin() const {
			return Iterator(_root);
		}
		Iterator end() const {
			return Iterator(nullptr);
		}

		void push(Type what) {
			if (_root == nullptr) {
				_root = new Node(what);
				_back = _root;
			} else {
				_back->next = new Node(what);
				_back = _back->next;
			}
		}
		Type pop() {
			auto removed = _root;
			auto result = removed->value;

			_root = _root->next;

			delete removed;

			return result;
		}

		void clear() {
			while (_root) {
				auto removed = _root;
				_root = _root->next;
				delete removed;
			}
		}

		void merge(const RequestQueue&& another) {
			for (const auto& it : another)
				push(it);
		}
		void merge(RequestQueue&& another) {
			_back->next = another._root;
			_back = another._back;
		}

	private:
		Node* _root, * _back;
	};
}