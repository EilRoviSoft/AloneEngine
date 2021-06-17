#include <SFML/Graphics/RenderWindow.hpp>
#include <atl/ui/TextBox.hpp>
#include <atl/manager/UiRenderer.hpp>

sf::RenderWindow window(sf::VideoMode(800, 600), "Window!");
namespace ui = atl::ui;
using namespace atl::manager;

int main() {
	UiRenderer renderer;

	sf::Font font;
	font.loadFromFile("res/settings/ptserif.ttf");
	
	ui::Element element(new ui::TextBox());
	auto tb = std::dynamic_pointer_cast <ui::TextBox>(element);

	tb->text->setFont(font);
	tb->loadFromFile("res/ui/test.xml");

	renderer.add(element);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear();
		
		renderer.render(window);

		window.display();
	}

	return 0;
}