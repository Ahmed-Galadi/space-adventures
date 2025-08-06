
#include "Player.hpp"
#include "Ship.hpp"
#include <iostream>

Player::Player(sf::RenderWindow &window, const std::string &name) :
	Ship(name, 100, 100), window(window), xPos(WIDTH/2), yPos(HEIGHT/2),
	playerTexture("/Users/agaladi/Downloads/spaceCraft.png"), playerImage(playerTexture) {
		playerImage.setPosition({xPos, yPos});
		window.draw(playerImage);
		std::cout << "Player is Created!!" << std::endl;
}

Player::~Player() {}

void	Player::lunchProject() {
	Missile m(name, true, 0, xPos, yPos);
	missiles.push_back(m);
	if (missiles.size() == 0)
		std::cout << "empty tank!" << std::endl;
}

sf::RenderWindow &Player::getWin() {
	return (this->window);
}

void	Player::move(float x, float y) {
	xPos += x;
	yPos += y;
	playerImage.setPosition({xPos, yPos});
	window.draw(playerImage);
}

void	Player::levelUp(int amount) {
	this->level += amount;
}

void	Player::drawPlayer() {
	window.draw(this->playerImage);
	// if (missiles.size()) {
	// 	window.draw(missiles[0].shot());
	// 	std::cout << "here! " << missiles[0].getShooter() << std::endl;
	// }
}
