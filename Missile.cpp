

#include "Player.hpp"
#include "Missile.hpp"

class Player;

Missile::Missile(std::string &shooter, bool isPlayer, int level, float x, float y) :
	shooterName(shooter), isPlayer(isPlayer), level(0), xPos(x), yPos(y) {
		missileShape.setFillColor(sf::Color::Black);
}

Missile::~Missile() {}

sf::RectangleShape	&Missile::shot() {
	missileShape.setPosition({xPos, yPos});
	yPos -= 5.0f;
	return (missileShape);
}

std::string Missile::getShooter() const {
	return (shooterName);
}