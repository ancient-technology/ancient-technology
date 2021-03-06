#include "renderer.h"


Renderer::Renderer(sf::RenderWindow *window, GameState *state)
{
	m_wnd = window;
	m_gst = state;

	// Load all the textures
	if (!m_texture_background.loadFromFile("assets/bg_yellow.png"))
	{
    	m_wnd->close();
    }
    m_texture_background.setRepeated(true);

    if (!m_texture_player.loadFromFile("assets/robot.png"))
	{
    	m_wnd->close();
    }

    if (!m_texture_screws.loadFromFile("assets/screws.png"))
	{
    	m_wnd->close();
    }

    // Load all the fonts
    if (!m_normal_font.loadFromFile("assets/Roboto-Regular.ttf"))
    {
    	m_wnd->close();
    }

    if (!m_bold_font.loadFromFile("assets/Roboto-Bold.ttf"))
    {
    	m_wnd->close();
    }

}

void Renderer::drawGame()
{
	m_wnd->clear();
	
	
	

	

	if(m_gst->getGameState() == STATE_MENU)
	{
		// Menu texts
		sf::Text text_title;
		text_title.setFont(m_bold_font);
		text_title.setString("Larry Screweater");
		text_title.setCharacterSize(80);
		text_title.setPosition(sf::Vector2f(m_wnd->getSize().x/2 - text_title.getLocalBounds().width/2,200));
		m_wnd->draw(text_title);

		sf::Text text_help;
		text_help.setFont(m_normal_font);
		text_help.setString("Larry the robot likes to eat screws. Help him by controlling his movements with the arrow keys.\nBe careful! You will lose the game when too many screws are visible. Start with the <SPACE> key.");
		text_help.setCharacterSize(20);
		text_help.setPosition(sf::Vector2f(m_wnd->getSize().x/2 - text_help.getLocalBounds().width/2,500));
		m_wnd->draw(text_help);
		
		sf::Sprite sprite_background;
		sprite_background.setTexture(m_texture_background);
		sprite_background.setTextureRect(sf::IntRect(0,0,m_wnd->getSize().x,m_wnd->getSize().y));
		m_wnd->draw(sprite_background);
		
		
	}
	else if(m_gst->getGameState() == STATE_SHOP)
	{
		m_wnd->draw(*m_gst->shop);
	}
	else
	{
		sf::View view = sf::View(m_gst->player->getPosition(), sf::Vector2f(1280,800));
		m_wnd->setView(view);

		sf::Sprite sprite_background;
		sprite_background.setTexture(m_texture_background);
		sprite_background.setTextureRect(sf::IntRect(0,0,m_gst->level->getBounds().x,m_gst->level->getBounds().y));
		m_wnd->draw(sprite_background);

		
		sf::Sprite sprite_screws;
		sprite_screws.setTexture(m_texture_screws);

		std::vector<sf::Vector2f> screws = m_gst->getScrewLocations();
		std::vector<sf::Vector2f>::iterator s_it;
		
		for(s_it = screws.begin();s_it != screws.end();s_it++)
		{
			sprite_screws.setPosition(*s_it);
			m_wnd->draw(sprite_screws);
		}
		//wall test
		//Wall test(sf::FloatRect(0,0,80,80),m_texture_screws);
		//m_wnd->draw(test);
		
		//Level test
		//Level ltest("levels/level0.dat");
		m_wnd->draw(*m_gst->level);
		
		//sf::Sprite sprite_player;
		//sprite_player.setTexture(m_texture_player);
		//sprite_player.setPosition(m_gst->player->getPosition());
		//m_wnd->draw(sprite_player);
		m_wnd->draw(*m_gst->player);
		
		

		
		
		
		
	}
	
	m_wnd->display();

}
