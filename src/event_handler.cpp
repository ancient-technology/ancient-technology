#include "event_handler.h"

EventHandler::EventHandler(sf::RenderWindow *window, GameState *state)
{
	m_wnd = window;
	m_gst = state;
	s = SoundHandler::getSoundHandler();
}

void EventHandler::handleEvents()
{
	sf::Event event;
    while (m_wnd->pollEvent(event))
    {
        // Close window : exit
        if (event.type == sf::Event::Closed)
        {
            m_wnd->close();
        }

        // Start playing when SPACE is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_gst->getGameState() == STATE_MENU)
        {
        	m_gst->startPlaying();
        }

		if(m_gst->getGameState() == STATE_PLAYING) {
			// Get robot direction
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					m_gst->player->setMovementDirection(DIRECTION_LEFT_UP);
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					m_gst->player->setMovementDirection(DIRECTION_LEFT_DOWN);
				else
					m_gst->player->setMovementDirection(DIRECTION_LEFT);
			//	hero->setOrientation(DIRECTION_LEFT);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					m_gst->player->setMovementDirection(DIRECTION_RIGHT_UP);
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					m_gst->player->setMovementDirection(DIRECTION_RIGHT_DOWN);
				else
					m_gst->player->setMovementDirection(DIRECTION_RIGHT);
			//	hero->setOrientation(DIRECTION_RIGHT);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				m_gst->player->setMovementDirection(DIRECTION_UP);
			//	hero->setOrientation(DIRECTION_UP);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				m_gst->player->setMovementDirection(DIRECTION_DOWN);
			//	hero->setOrientation(DIRECTION_DOWN);
			}
			else
			{
				m_gst->player->setMovementDirection(DIRECTION_NONE);
			} //*/
		}
		else if (m_gst->getGameState() == STATE_SHOP)
		{
			if(event.type == sf::Event::KeyPressed)
			{
				switch(event.key.code)
				{
					case sf::Keyboard::S:
						m_gst->shop->upgradeSchuhe();
						break;
					case sf::Keyboard::Q:
						m_gst->m_game_state = STATE_PLAYING;
						break;
				}
			}
		}
        
        if(event.type == sf::Event::KeyPressed)
		{
			switch(event.key.code)
			{
				case sf::Keyboard::M:
					s->toggleMute();
					break;
			}
		}
		
	}
}
