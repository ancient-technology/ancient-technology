#ifndef PLAYER_H
#define PLAYER_H

#include "level.h"
#include <SFML/Graphics.hpp>

#define DIRECTION_NONE 0
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT 2
#define DIRECTION_UP 3
#define DIRECTION_DOWN 4

#define DIRECTION_LEFT_UP 5
#define DIRECTION_RIGHT_UP 6
#define DIRECTION_LEFT_DOWN 7
#define DIRECTION_RIGHT_DOWN 8

class Player: public sf::Drawable
{
public:
	Player();
	Player(Level* lev);
	void move();
//	void addMoveVector(sf::Vector2f move);
	sf::Vector2f getPosition();
	void setMovementDirection(int direction);
	//int getCollectedCoins();
	//int getOrientation();
	//void setOrientation(int newOrientation);
	//void shoot();
	//start/stop shooting // setzt shooting
	//void startShooting();
	//void stopShooting();
	
	//prüft ob player lebt und gibt lebenspunkte zurück
	//float checkLife();
	void resetLevel(Level* level);
	
private:
	virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const;
	sf::Vector2f position;
	void initPlayer();
	sf::Vector2f moveVector;
	Level* level;
	int collectedCoins;
	
	//int orientation;
	void onDeath();
	
	float movementSpeed;
	

	sf::Texture tex_player ;

	
	//soundhandler
	//SoundHandler* s;
	
	//space gedrückt?
	//bool shooting;
	//bestimmt wie lange hero noch bis zum nächsten schuss warten muss
	//float shoot_threshold;
	//bestimmt wie lange die pause zwischen schüssen ist
	//float reload_time;

};

#endif
