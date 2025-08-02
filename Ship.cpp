#include "Ship.hpp"

Ship::Ship(const unsigned int power, const unsigned int defence) : name("enemy"), health(100), power(power), defence(defence), luck(0), speed(100), level(-999) {}

Ship::Ship(const std::string &name, const unsigned int power, const unsigned int defence) : name("name"), health(100), power(power), defence(defence), luck(0), speed(100), level(0) {}

bool	Ship::operator>(const Ship &other) {
	return (this->defence > other.defence);
}

bool	Ship::operator<(const Ship &other) {
	return (this->defence < other.defence);
}

Ship::~Ship() {}

void	Ship::levelUp(int amount) {
	this->level += amount;
}

void	Ship::getDamage(const Ship &other) {
	int leftDamage;
	if (this->defence - other.power >= 0)
		this->defence -= other.power;
	else {
		leftDamage = other.power - this->defence;
		this->defence = 0;
		if (leftDamage > this->health)
			getDestroyed();
		else
			this->health -= leftDamage;
	}
}

void	Ship::attack(Ship &other) {
	other.getDamage(*this);
}

void	Ship::healthUp(int amount) {
	this->health += amount;
}

void	Ship::powerUp(int amount) {
	this->power += amount;
}

void	Ship::speedUp(int amount) {
	this->speed += amount;
}

void	Ship::getLucky(int amount) {
	this->luck += amount;
}

void	Ship::getInvisible() {
	this->isInvisible = true;
}

void	Ship::godMode() {
	this->isGod = true;
}

void	Ship::getCursed() {
	this->isCursed = true;
}

void	Ship::getPoisened(int amount) {
	this->isPoisened = true;
}

void 	Ship::getDestroyed() {}