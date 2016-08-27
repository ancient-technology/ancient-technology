#ifndef WALL_H
#define WALL_H

#include <SFML/Graphics.hpp>

class Wall : public sf::Drawable
{
public:
	Wall(sf::FloatRect pos,sf::Texture tex);
	sf::Vector2f getPosition();
	sf::FloatRect getRect();
	bool isCollision(sf::Vector2f entPosition,sf::FloatRect* box);

private:
	virtual void draw(sf::RenderTarget& target,sf::RenderStates states)const;

	sf::Vector2f position;
//	void draw(sf::RenderTarget& target, sf::RenderStates states);
	sf::FloatRect rect;
	sf::Texture texture;
};

#endif
