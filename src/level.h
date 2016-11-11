#ifndef LEVEL_H
#define LEVEL_H

#define ROBOTSIZE 80
#define WALLSIZE 80
#define SCREWSIZE 80

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
	int screwCollision(sf::Vector2f position,sf::FloatRect* box);
	
	bool isExit(sf::Vector2f position,sf::FloatRect* box);
	bool isWorkbench(sf::Vector2f position,sf::FloatRect* box);
//	bool isCollision(sf::Vector2f entPosition,sf::FloatRect* box);
	sf::Vector2f getBounds();
	
	void setNextLevel(std::string nxtLevelPath);
	std::string getNextLevel();

private:
	virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const;

	sf::Vector2f levelBounds;
	sf::Texture texture;
	
	// first char of levelpath
	char* beginLevelPath;
	
	// init level
	void initLevel();
	
	std::list<Wall> walls;
	
	std::list<sf::Vector2f> screw_locations;
	
	Wall exit;
	Wall workbench;
	
	sf::Texture tex_wall;
	sf::Texture tex_exit;
	sf::Texture tex_screws;
	sf::Texture tex_workbench;
	
	sf::Vector2f playerStart;
	
	std::string nextLevelPath;
};

#endif
