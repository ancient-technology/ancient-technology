#ifndef SHOP_H
#define SHOP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include "player.h"

class Shop : public sf::Drawable
{
public:
	Shop(Player* p);
	void upgradeSchuhe();
	
private:
	virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const;
	Player* player;
	
	sf::Font roboto_bold;
};

#endif
