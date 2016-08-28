#include "sound_handler.h"
//Singleton Class


//constructor
SoundHandler::SoundHandler()
{
	bgVolume = 60;
	muted = 1;
	soundVolume = 100;
	loadBuffers();
	
}



sf::SoundBuffer gun;
sf::SoundBuffer gun_dry;
sf::SoundBuffer chambering;
								
SoundHandler* SoundHandler::s = NULL;

SoundHandler* SoundHandler::getSoundHandler()
{
	// if there is no SoundHandler build new one
	if(s == NULL)
	{
		s = new SoundHandler;
		
	}
	return s;
}



void SoundHandler::playSound(int soundNumber)
{
	if(!muted)
	{
		
	}
}


void SoundHandler::playBg()
{
	bgMusic.setBuffer(bgMusicBuff);
	bgMusic.play();
	bgMusic.setLoop(true);
	bgMusic.setVolume(bgVolume);
}



void SoundHandler::toggleMute()
{
	
	bgMusic.setVolume(muted * bgVolume); 
	muted ^= 1; //invertieren
}


void SoundHandler::setBgVolume(float volume)
{
	bgVolume = volume;
	bgMusic.setVolume(volume);
}


void SoundHandler::setSoundVolume(float volume)
{
	soundVolume = volume;
}

void SoundHandler::loadBuffers()
{
	bgMusicBuff.loadFromFile("sfx/bg/Temple_of_the_Mystics.wav");
	//gun.loadFromFile("sfx/sounds/GunFire.wav");
	//gun_dry.loadFromFile("sfx/sounds/DryFire.wav");
	//chambering.loadFromFile("sfx/sounds/Chambering.wav");
}

void SoundHandler::del()
{
	delete s;
}
