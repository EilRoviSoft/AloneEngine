#include "UiRenderer.hpp"

void atl::UiRenderer::prerender(GameWindow& target, sf::RenderStates states) const {
	for (const auto& it : _layers)
			target.draw(*it);
}
void atl::UiRenderer::render(GameWindow& target, sf::RenderStates states) const {
	for (const auto& it : _onUpdateElements)
		target.draw(**it);
}

atl::UiRenderer::Iterator atl::UiRenderer::findByName(const std::string& name) const {
	auto id = hash(name);

	return std::find_if(_layers.begin(), _layers.end(), [id](const UiElement& _it) {
		return _it->getId() == id;
	});
}

atl::UiRenderer::Iterator atl::UiRenderer::add(UiElement what) {
	_layers.push_back(what);

	auto it = std::prev(_layers.end());

	return it;
}
atl::UiRenderer::Iterator atl::UiRenderer::add(UiElement what, Iterator where) {
	auto it = _layers.insert(where, what);
	return it;
}

atl::UiRenderer::Iterator atl::UiRenderer::changeOrder(Iterator what, ptrdiff_t offset) {
	auto copy = what;
	std::advance(copy, offset);

	std::swap(what, copy);

	return what;
}

atl::UiRenderer::Iterator atl::UiRenderer::remove(Iterator where) {
	if (where == _layers.end())
		return _layers.end();
	return _layers.erase(where);
}
