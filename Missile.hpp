
#pragma once

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Player;

class Missile {
	private:
		std::string shooterName;
		bool 		isPlayer;
		int 		level;
		sf::RectangleShape missileShape;
		float		xPos;
		float		yPos;
	
	public:
		Missile(std::string &shooter, bool isPlayer, int level, float x, float y);
		~Missile();

		sf::RectangleShape	&shot();
		std::string getShooter() const;
};