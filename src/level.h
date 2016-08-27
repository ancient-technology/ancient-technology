#ifndef LEVEL_H
#define LEVEL_H

#define ROBOTSIZE 80
#define WALLSIZE 80

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <list>
#include "wall.h"

class Level : public sf::Drawable
{
public:
	Level();
	Level(std::string levelPath);
	sf::Vector2f getPlayerStart();
	//manipuliert den moveVector sodass man nur bis zur Wand läuft
	sf::Vector2f wallCollision(sf::Vector2f position,sf::FloatRect* box,sf::Vector2f moveVector);
//	bool isCollision(sf::Vector2f entPosition,sf::FloatRect* box);
	sf::Vector2f getBounds();

private:
	virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const;

	sf::Vector2f levelBounds;
	sf::Texture texture;
	
	// first char of levelpath
	char* beginLevelPath;
	
	// init level
	void initLevel();
	
	std::list<Wall> walls;
	
	sf::Texture tex_wall;
	
	sf::Vector2f playerStart;
};

#endif
