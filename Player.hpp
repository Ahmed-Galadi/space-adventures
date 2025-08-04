
#pragma once

#include <SFML/Graphics.hpp>
#include "Ship.hpp"
#include "Missile.hpp"

#define HEIGHT		1000
#define WIDTH		800

class Player : public Ship {
	private:
		sf::RenderWindow &window;
		sf::Texture playerTexture;
		sf::Sprite playerImage;
		float		xPos;
		float		yPos;
		std::vector<Missile> missiles;

	public:
		Player(sf::RenderWindow &window,const std::string &name);
		~Player();

		void lunchProject();
		void move(float x, float y);
		void drawPlayer();
		virtual void levelUp(int amount);
		sf::RenderWindow &getWin();
};
