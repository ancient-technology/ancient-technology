#include "wall.h"


Wall::Wall(sf::FloatRect rect,sf::Texture tex)
{
	//set walls position
	position = sf::Vector2f(rect.left,rect.top);
	
	//init rect
	this->rect = rect;
	
	texture = tex;
}


// get rect
sf::FloatRect Wall::getRect()
{
	return rect;
}

sf::Vector2f Wall::getPosition()
{
	return position;
}
bool Wall::isCollision(sf::Vector2f entPosition,sf::FloatRect* box)
{
	sf::Vector2f distance = position - entPosition;
	//	std::cout<< "distance: (" << distance.x << "," << distance.y <<")\n";
	//std::cout << (distance.x*distance.x + distance.y*distance.y) /(80*80)<< "\n";
	 
	// 					  x^2 + y^2 				   < wurzel(2) * 80^2
	//if((distance.x*distance.x + distance.y*distance.y) < 9051)
		if(rect.intersects(*box))
		{
			return true;
		//	std::cout << "collision: " << collision;
		}
}

void Wall::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
	sf::Sprite sprite_wall;
	sprite_wall.setTexture(texture);
	
	//sprite_wall.setTextureRect((sf::IntRect)rect);
	sprite_wall.setPosition(position);
	target.draw(sprite_wall);
}
