#pragma once

#include <string>

class Ship {
	protected:
		std::string		name;
		unsigned int	health;
		unsigned int	power;
		unsigned int	defence;
		unsigned int 	luck;
		unsigned int	speed;
		int 			level;
		bool 			isGod;
		bool			isInvisible;
		bool			isCursed;
		bool			isPoisened;
	
	public:
		Ship(const unsigned int power, const unsigned int defence);
		Ship(const std::string &name, const unsigned int power, const unsigned int defence);
		bool 	operator>(const Ship &other);
		bool 	operator<(const Ship &other);
		~Ship();

		virtual void	levelUp(int amount) = 0;
		void			getDamage(const Ship &other);
		void 			attack(Ship &other);
		void 			healthUp(int amount);
		void 			powerUp(int amount);
		void			speedUp(int amount);
		void			getLucky(int amount);
		void 			getInvisible();
		void			godMode();
		void			getCursed();
		void			getPoisened(int amount);
		void			getDestroyed(void);
};
