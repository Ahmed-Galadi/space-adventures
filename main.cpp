

#include <SFML/Graphics.hpp>
#include "Player.hpp"

#define BGABSPOS	-6950.0f
#define HEIGHT		1000
#define WIDTH		800

int main() {
	sf::RenderWindow window(sf::VideoMode({WIDTH, HEIGHT}), "Space Adventure");
	// background
	const sf::Texture t("/Users/agaladi/Downloads/level1Background.png");
	sf::Sprite img(t);
	float 	bgAbsPos = BGABSPOS;
	img.setScale({7.95f, 7.95f});
	img.setPosition({0.0f, bgAbsPos});
	//Player
	Player p(window, "Ahmed");
	// ***************************************
	while (window.isOpen()) {
		while (const std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>())
				window.close();
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        	{
            	if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                	window.close();
				else if (keyPressed->scancode == sf::Keyboard::Scancode::Up) 
					p.move(0, -5.0);
				else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) 
					p.move(0, 5.0);
				else if (keyPressed->scancode == sf::Keyboard::Scancode::Left) 
					p.move(-5.0, 0);
				else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) 
					p.move(5.0, 0);
				else if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
					p.lunchProject();
			}
		}

		window.clear();
		if (bgAbsPos <= 0) {
			bgAbsPos += 0.01;
			img.setPosition({0.0f, bgAbsPos});
		}
		if (bgAbsPos>=0)
			bgAbsPos = BGABSPOS;
		window.draw(img);
		p.drawPlayer();
		// p.
		window.display();
	}
 	return (0);
}

