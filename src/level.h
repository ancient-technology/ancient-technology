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
	sf::Vector2f getPosition();
	sf::FloatRect getRect();
	bool isCollision(sf::Vector2f entPosition,sf::FloatRect* box);

private:
	virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const;

	sf::Vector2f position;
	sf::FloatRect rect;
	sf::Texture texture;
	sf::View view;
	
	// first char of levelpath
	char* beginLevelPath;
	
	// init level
	void initLevel();
	
	std::list<Wall> walls;
	
	sf::Texture tex_wall;
};

#endif
