#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window(sf::VideoMode({800, 1000}), "Space Adventure");
	const sf::Texture t("/Users/agaladi/Downloads/level1Background.png");
	sf::Sprite img(t);
	float 	bgAbsPos = -6950.0f;

	img.setScale({7.95f, 7.95f});
	img.setPosition({0.0f, bgAbsPos});
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        	{
            	if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                	window.close();
        	}
		}

		window.clear();
		if (bgAbsPos < 0)
			img.setPosition({0.0f, bgAbsPos++});
		window.draw(img);
		window.display();
	}
 	return (0);
}

