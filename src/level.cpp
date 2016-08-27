#include "level.h"

Level::Level(){};

Level::Level(std::string levelPath)
{
	beginLevelPath = &levelPath.at(0);
	
	tex_wall.loadFromFile("assets/screws.png");
	
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
    	col = 0;
    	for(; col+2 < line.length();++col)
    	{
    		switch(line[col+1])
    		{
    			//Player
    			case 'p':
    			case 'P':
    	//			playerStart = (sf::Vector2f(col*ROBOTSIZE,row*ROBOTSIZE));
    				break;
    				
    			//Wall
    			case 'x':
    			case 'X':
					//std::cout<<"push wall \n";
					Wall newWall(sf::FloatRect(col*WALLSIZE,row*WALLSIZE,WALLSIZE,WALLSIZE),tex_wall);
					//Wall newWall(sf::FloatRect(50,10,WALLSIZE,WALLSIZE),tex_wall);
					//std::cout<<"(" << newWall.getRect().left <<","<< newWall.getRect().top <<")   "  << "push wall \n";
					walls.push_back(newWall);
					std::cout << col << "  " << row << "\n";
					std::cout<< walls.size() << "\n";
					break;
    		}
    		
    	}
    }
    // bestimme levelbounds
    //levelBounds = sf::Vector2f(col,row); 
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
}
