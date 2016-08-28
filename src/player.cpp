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
//	collectedCoins = 0;
//	orientation = DIRECTION_LEFT;
//	s = SoundHandler::getSoundHandler();
//	shooting = false;
//	reload_time = 40;
//	shoot_threshold = 0;
//	leben = 100.0f;
	tex_player.loadFromFile("assets/robot_ani.png");
	ani = new Animation();
	ani->setSpriteSheet(tex_player);
	ani->addFrame(sf::IntRect(0, 0, 80, 80));
	ani->addFrame(sf::IntRect(80, 0, 80, 80));

	animatedSprite = new AnimatedSprite(sf::seconds(0.2), true, false);
}


void Player::move()
{
	
	
	
	sf::Vector2f mV = moveVector*movementSpeed;
	
	std::cout << "move\n" << mV.x << "  " <<mV.y<<"\n";
	
	
	
	// Bounding box of the player(after the move)
	sf::FloatRect* player_box = new sf::FloatRect(position + mV,sf::Vector2f(ROBOTSIZE,ROBOTSIZE));
	
	mV = level->wallCollision(position,player_box,mV);
	
	// Update the player location
	sf::Vector2f new_location(position + mV);
	//std::cout << "pos: " << position.x << "," << position.y << "\n";
	

	std::cout << "move\n" << mV.x << "  " <<mV.y<<"\n";

	
	
	// Check if new position is inside the game area
	if(new_location.x >= 0
		&& new_location.x + ROBOTSIZE <= level->getBounds().x*WALLSIZE
		&& new_location.y >= 0
		&& new_location.y + ROBOTSIZE <= level->getBounds().y*WALLSIZE)
	{
	//	std::cout<< collision << "\n";
		position = new_location; // Update location
	}
	/*
	//collect coins
	std::vector<sf::Vector2f>*  coins = level->getCoins();
	std::vector<sf::Vector2f>::iterator coin_it;
	// Check for each coin ...
	for(coin_it = level->getCoins()->begin();coin_it != level->getCoins()->end();)
	{
		sf::FloatRect coinRect(*coin_it,sf::Vector2f(COIN_WIDTH,COIN_HEIGHT));
		if(coinRect.intersects(player_box))
		{
			collectedCoins++;
			
			level->getCoins()->erase(coin_it);
		//	std::cout<<"coins: " << collectedCoins<<"\n";
		}
		else
			coin_it++;
	} //*/
	
	animatedSprite->update(sf::seconds(0.02));
	animatedSprite->setPosition(position);
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
		//moveVector = sf::Vector2f(0,0);
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
	this->level = level;
	position = level->getPlayerStart();
}

void Player::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
	/*sf::Sprite sprite_playeVr;
	sprite_player.setTexture(tex_player);
	sprite_player.setPosition(position);
	
	target.draw(sprite_player);*/

	sf::Time t = sf::seconds(0.2);
	animatedSprite->play(*ani);
	target.draw(*animatedSprite);
}
