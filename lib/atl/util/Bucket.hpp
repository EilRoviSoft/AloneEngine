#pragma once
//std
#include <xutility> //find, next, prev
#include <list> //list

namespace atl::util {
	//TODO: Bucket <Type> with minimal_difference
	class Bucket {
	public:
		using Iterator = std::list <size_t>::iterator;

		//0 is reserved starting value
		Bucket() : m_storage() {
			m_storage.push_back(0);
			m_minConsecutiveValue = m_storage.begin();
		}

		size_t allocate() {
			size_t result = *m_minConsecutiveValue + 1;

			if (m_minConsecutiveValue == std::prev(m_storage.end())) {
				m_storage.push_back(result);
				m_minConsecutiveValue = std::prev(m_storage.end());
			} else {
				m_minConsecutiveValue = _findNewMinConsecutivePlace(
					m_storage.insert(std::next(m_minConsecutiveValue), result));
			}

			return result;
		}

		void free(size_t _hash) {
			auto it = _findByHash(_hash);
			if (it == m_storage.end())
				return;

			auto removed = m_storage.erase(it);

			if (_hash <= *m_minConsecutiveValue)
				m_minConsecutiveValue = std::prev(removed);
		}

	protected:
		std::list <size_t> m_storage;
		Iterator m_minConsecutiveValue;

	private:
		Iterator _findNewMinConsecutivePlace(Iterator _start) {
			Iterator it = _start, nit = std::next(_start);
			for (; nit != m_storage.end(); it++, nit++)
				if (*nit - *it != 1)
					return nit;

			return it;
		}
		Iterator _findByHash(size_t _hash) {
			return std::find(m_storage.begin(), m_storage.end(), _hash);
		}
	};
}