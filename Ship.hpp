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
	
	public:
		Ship();
		Ship(const std::string &name);
		bool 	operator>(const Ship &other);
		bool 	operator<(const Ship &other);
		~Ship();

		virtual void	levelUp(int amount) = 0;
		void			getDamage(const Ship &other);
		void 			attack(const Ship &other);
		void 			deffend(const Ship &other);
		void 			healthUp(int amount);
		void 			powerUp(int amount);
		void			speedUp(int amount);
		void			getLucky(int amount, int time);
		void 			getInvisible(int time);
		void			godMode(int time);
		void			getCursed(int time);
		void			getPoisened(int time, int ammount);
};
