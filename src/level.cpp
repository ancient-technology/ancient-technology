#include "level.h"

Level::Level(){};

Level::Level(std::string levelPath)
{
	beginLevelPath = &levelPath.at(0);
	
	tex_wall.loadFromFile("assets/wall.png");
	tex_exit.loadFromFile("assets/exit.png");
	tex_screws.loadFromFile("assets/screws.png");
	tex_workbench.loadFromFile("assets/workbench.png");
	
	//
	initLevel();
}

void Level::initLevel()
{
	std::string line = "42";
	//ifstream brauch const char* bzw const string aka "blablub"
	const char* myPath = beginLevelPath;
    std::ifstream infile(myPath);
    
    int numberOfScrews = 0;
    
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
    		else if(line[1] == 'S')
    		{
    			//line = line.substr(3);
    			std::string l = line;
    			numberOfScrews = atoi(l.substr(3).c_str());
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
					//Player
					case 's':
					case 'S':
						screw_locations.push_back(sf::Vector2f(col*WALLSIZE,row*WALLSIZE));
						break;
					
					//exit
					case 'w':
					case 'W':
						//std::cout<<"push wall \n";
						workbench = Wall(sf::FloatRect(col*WALLSIZE,row*WALLSIZE,WALLSIZE,WALLSIZE),tex_workbench);
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
    
    for(int i = 0; i < numberOfScrews;i++)
    {
		// New random position for screw inside the game area
		float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(levelBounds.x-SCREWSIZE)));
		float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(levelBounds.y-SCREWSIZE)));
		screw_locations.push_back(sf::Vector2f(x,y));
    }
}

void Level::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
	sf::Sprite sprite_screws;
	sprite_screws.setTexture(tex_screws);

	for(std::list<sf::Vector2f>::const_iterator s_it = screw_locations.begin();s_it != screw_locations.end();s_it++)
	{
		sprite_screws.setPosition(*s_it);
		target.draw(sprite_screws);
	}

	//draw walls
	sf::Sprite sprite_wall;
	sprite_wall.setTexture(tex_wall);
	
	//std::cout << walls.size()<< " level \n";
	
	for (std::list<Wall>::const_iterator it = walls.begin(); it != walls.end(); it++)
   	{
		target.draw(*it);
		
   	}  //*/
   	target.draw(exit);
   	target.draw(workbench);
   	
   	
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

int Level::screwCollision(sf::Vector2f position,sf::FloatRect* box)
{
	int screws_collected = 0;
	for (std::list<sf::Vector2f>::iterator it = screw_locations.begin(); it != screw_locations.end();)
   	{
		// ... if the robot is "eating" the screw
		sf::FloatRect screw_box(*it,sf::Vector2f(SCREWSIZE,SCREWSIZE));
		if(screw_box.intersects(*box))
		{
			std::cout << it->x << " \n ";
			// Remove screw
			it = screw_locations.erase(it);
			screws_collected++;
		}
		else
		{
			// Advance iterator to next screw
			++it;
		}
		
   	} 
	return screws_collected;
}

bool Level::isExit(sf::Vector2f position,sf::FloatRect* box)
{
	return exit.isCollision(position,box);
}

bool Level::isWorkbench(sf::Vector2f position,sf::FloatRect* box)
{
	return workbench.isCollision(position,box);
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
