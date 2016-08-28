#include "player.h"

Player::Player()
{
	
}


Player::Player(Level* lev)
{
	moveVector = sf::Vector2f(0,0);
	position = lev->getPlayerStart();
//	std::cout << "pos: " << position.x << "," << position.y << "\n";
//	initPlayer();
	movementSpeed = 8;
	level = lev;
	collectedScrews = 0;
//	orientation = DIRECTION_LEFT;
//	s = SoundHandler::getSoundHandler();
//	shooting = false;
//	reload_time = 40;
//	shoot_threshold = 0;
//	leben = 100.0f;
	tex_player.loadFromFile("assets/robot.png");
	roboto_bold.loadFromFile("assets/Roboto-Bold.ttf");


}


void Player::move()
{
	
	
	
	sf::Vector2f mV = moveVector*movementSpeed;
	
	//std::cout << "move\n" << mV.x << "  " <<mV.y<<"\n";
	
	
	
	// Bounding box of the player(after the move)
	sf::FloatRect* player_box = new sf::FloatRect(position + mV,sf::Vector2f(ROBOTSIZE,ROBOTSIZE));
	
	//check if hit exit
	if(level->isExit(position + mV,player_box))
	{
		resetLevel(new Level(level->getNextLevel()));
		std::cout << "Exit\n";
	}
	
	//check for wall Collisions
	mV = level->wallCollision(position,player_box,mV);
	
	// Update the player location
	sf::Vector2f new_location(position + mV);
	//std::cout << "pos: " << position.x << "," << position.y << "\n";
	

	//std::cout << "move\n" << mV.x << "  " <<mV.y<<"\n";

	
	
	// Check if new position is inside the game area
	if(new_location.x >= 0
		&& new_location.x + ROBOTSIZE <= level->getBounds().x
		&& new_location.y >= 0
		&& new_location.y + ROBOTSIZE <= level->getBounds().y)
	{
	//	std::cout<< collision << "\n";
		position = new_location; // Update location
	}
	collectedScrews += level->screwCollision(position,player_box);
	
}

void Player::setMovementDirection(int direction)
{
	switch(direction)
	{
		case DIRECTION_LEFT:
		moveVector = sf::Vector2f(-1,0);
		break;

		case DIRECTION_LEFT_UP:
		moveVector = sf::Vector2f(-1,-1);
		break;
		
		case DIRECTION_LEFT_DOWN:
		moveVector = sf::Vector2f(-1,1);
		break;

		case DIRECTION_RIGHT:
		moveVector = sf::Vector2f(1,0);
		break;
		
		case DIRECTION_RIGHT_UP:
		moveVector = sf::Vector2f(1,-1);
		break;
		
		case DIRECTION_RIGHT_DOWN:
		moveVector = sf::Vector2f(1,1);
		break;

		case DIRECTION_UP:
		moveVector = sf::Vector2f(0,-1);
		break;

		case DIRECTION_DOWN:
		moveVector = sf::Vector2f(0,1);
		break;

		default:
		moveVector = sf::Vector2f(0,0);
		break;
	}
}


sf::Vector2f Player::getPosition()
{
	return position;
}

	

void Player::onDeath()
{

}
void Player::resetLevel(Level* level)
{
	*this->level = *level;
	position = level->getPlayerStart();
}

void Player::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
	sf::Sprite sprite_player;
	sprite_player.setTexture(tex_player);
	sprite_player.setPosition(position);
	target.draw(sprite_player);
	
	
	//draw stats
	std::stringstream str;
	str << collectedScrews << " Schrauben gesammelt\n";
	
	sf::Text stats;
	stats.setFont(roboto_bold);
	stats.setString(str.str());
	stats.setCharacterSize(30);
	stats.setPosition(position - sf::Vector2f(600,350));
	target.draw(stats);
}
