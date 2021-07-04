#include "UiRenderer.hpp"

void atl::UiRenderer::render(sf::RenderWindow& window) const {
	for (const auto& it : m_layers)
		if (it->m_onUpdate) {
			window.draw(*it);
			it->m_onUpdate = false;
		}
}

atl::UiRenderer::Iterator atl::UiRenderer::findByName(const std::string& name) const {
	auto id = hash(name);

	return std::find_if(m_layers.begin(), m_layers.end(), [id](const UiElement& _it) {
		return _it->getId() == id;
	});
}

atl::UiRenderer::Iterator atl::UiRenderer::add(UiElement what) {
	m_layers.push_back(what);

	auto it = std::prev(m_layers.end());

	return it;
}
atl::UiRenderer::Iterator atl::UiRenderer::add(UiElement what, Iterator where) {
	auto it = m_layers.insert(where, what);
	return it;
}

atl::UiRenderer::Iterator atl::UiRenderer::changeOrder(Iterator what, ptrdiff_t offset) {
	auto copy = what;
	std::advance(copy, offset);

	std::swap(what, copy);

	return what;
}

atl::UiRenderer::Iterator atl::UiRenderer::remove(Iterator where) {
	if (where == m_layers.end())
		return m_layers.end();
	return m_layers.erase(where);
}
