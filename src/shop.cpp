#include "shop.h"

Shop::Shop(Player* p)
{
	player = p;
	roboto_bold.loadFromFile("assets/Roboto-Bold.ttf");
};

void Shop::upgradeSchuhe()
{
	player->movementSpeed +=20;
}



void Shop::draw(sf::RenderTarget& target,sf::RenderStates states)const
{
	sf::View view(sf::Vector2f(640,400), sf::Vector2f(1280,800));
	target.setView(view);
   	
   	sf::Vector2f drawPos(0,0);
   	
   	float stufe_schuhe = (player->movementSpeed -4)/2;
   	
   	std::stringstream str;
	str << "Schuhe: \t" << static_cast<int>(stufe_schuhe) << " \t\t Upgradekosten: " << (stufe_schuhe*stufe_schuhe)+2*10 << " Bauteile \n";
	str << "\t\t"		<< "Zum Upgrade druecke S \n";
	str << "\n\n Zum Beenden druecke Q";
	  	 	
   	sf::Text schuhe;
	schuhe.setFont(roboto_bold);
	schuhe.setString(str.str());
	schuhe.setCharacterSize(30);
	schuhe.setPosition(drawPos);
	target.draw(schuhe);
}

