#include "level.h"

Level::Level(){};

Level::Level(std::string levelPath)
{
	beginLevelPath = &levelPath.at(0);
	
	tex_wall.loadFromFile("assets/wall.png");
	tex_exit.loadFromFile("assets/exit.png");
	
	//
	initLevel();
}

void Level::initLevel()
{
	std::string line = "42";
	//ifstream brauch const char* bzw const string aka "blablub"
	const char* myPath = beginLevelPath;
    std::ifstream infile(myPath);
    
    // init before for loop, because need after it for levelbounds
    int row = 0;
    int col = 0;
    //load walls etc
    for(; !std::getline(infile,line).eof();++row)
    {
    	if(line[0] == '#')
    	{
    		if(line[1] == 'E')
    		{
    			setNextLevel(line.substr(3));
    		}
    		//std::cout << line;
    	}
    	else
    	{
    		levelBounds.x =col*WALLSIZE;
    		levelBounds.y += WALLSIZE;
			col = -1;
			for(; col+2 <= line.length();++col)
			{
				switch(line[col+1])
				{
					//exit
					case 'e':
					case 'E':
						//std::cout<<"push wall \n";
						exit = Wall(sf::FloatRect(col*WALLSIZE,row*WALLSIZE,WALLSIZE,WALLSIZE),tex_exit);
						break;
				
					//Player
					case 'p':
					case 'P':
						playerStart = (sf::Vector2f(col*WALLSIZE,row*WALLSIZE));
						break;
						
					//Wall
					case 'x':
					case 'X':
						//std::cout<<"push wall \n";
						Wall newWall(sf::FloatRect(col*WALLSIZE,row*WALLSIZE,WALLSIZE,WALLSIZE),tex_wall);
						//Wall newWall(sf::FloatRect(50,10,WALLSIZE,WALLSIZE),tex_wall);
						//std::cout<<"(" << newWall.getRect().left <<","<< newWall.getRect().top <<")   "  << "push wall \n";
						walls.push_back(newWall);
						//std::cout << col << "  " << row << "\n";
						//std::cout<< walls.size() << "\n";
						break;
				
				}
				
			}
		}
    }
    // bestimme levelbounds
    //levelBounds = sf::Vector2f(col*WALLSIZE,row*WALLSIZE); 
    

    
}

void Level::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
	//draw walls
	sf::Sprite sprite_wall;
	sprite_wall.setTexture(tex_wall);
	
	//std::cout << walls.size()<< " level \n";
	
	for (std::list<Wall>::const_iterator it = walls.begin(); it != walls.end(); it++)
   	{
		target.draw(*it);
		
   	}  //*/
   	target.draw(exit);
}

sf::Vector2f Level::getPlayerStart()
{
	return playerStart;
}

sf::Vector2f Level::wallCollision(sf::Vector2f position,sf::FloatRect* box,sf::Vector2f moveVector)
{
	for (std::list<Wall>::iterator it = walls.begin(); it != walls.end(); it++)
   	{
		if(it->isCollision(position,box))
		{
			return sf::Vector2f(0,0);
		}
		
   	} 
	return moveVector;
}
bool Level::isExit(sf::Vector2f position,sf::FloatRect* box)
{
	return exit.isCollision(position,box);
}

sf::Vector2f Level::getBounds()
{
	return levelBounds;
}

void Level::setNextLevel(std::string nxtLevelPath)
{
	nextLevelPath =  nxtLevelPath;
}

std::string Level::getNextLevel()
{
	return nextLevelPath;
}
