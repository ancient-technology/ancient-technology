#include "game_state.h"

GameState::GameState(int x, int y)
{
	// Initial game state
	m_game_state = STATE_MENU;

	// Size of the game area
	m_size_x = x;
	m_size_y = y;

	// Set initial player movement and location
	setPlayerMovementDirection(DIRECTION_NONE);
		
	// Initialize random seed
	srand (static_cast <unsigned> (time(0)));
}

int GameState::getGameState()
{
	return m_game_state;
}

void GameState::startPlaying()
{
	m_game_state = STATE_PLAYING;
	
	level = new Level("levels/level0.dat");
	setPlayerLocation(level->getPlayerStart());
	player= new Player(level);

	// Reset all values
	m_screws_collected = 0;
	setPlayerMovementDirection(DIRECTION_NONE);
	m_screw_locations.clear();

}

void GameState::updateGameState()
{
	// Do nothing if the game is not in playing state
	if(m_game_state != STATE_PLAYING)
	{
		return;
	}

	// Return to menu state when losing the game
	/*if(getVisibleScrewsCount() >= 10)
	{
		m_game_state = STATE_MENU;
		return;
	}*/

	player->move();
	

	// Add a new screw when threshold value is reached
	m_new_screw_threshold += static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	if(m_new_screw_threshold > SCREW_SPAWN_THRESHOLD)
	{
		m_new_screw_threshold = 0;

	}
}

void GameState::setPlayerMovementDirection(int direction)
{
	m_player_direction = direction;
}

void GameState::setPlayerLocation(sf::Vector2f location)
{
	m_player_location = location;
}

sf::Vector2f GameState::getPlayerLocation()
{
	return m_player_location;
}

void GameState::addScrew(sf::Vector2f location)
{
	m_screw_locations.push_back(location);
}

std::vector<sf::Vector2f> GameState::getScrewLocations()
{
	return m_screw_locations;
}

int GameState::getVisibleScrewsCount()
{
	return m_screw_locations.size();
}

int GameState::getCollectedScrewsCount()
{
	return m_screws_collected;
}
