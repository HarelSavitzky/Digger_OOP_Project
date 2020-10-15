#pragma once
//--------------------include Section --------------------
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Const.h"
#include <iostream>

//--------------------Sounds Class definition --------------------
class Sounds
{
public:
	Sounds();
	//sounds definitino------
	void defineSound();

	//handle sounds-------
	void playSound(int sound);
	void startMusic(int music, int volume);
	void stopMusic(int music);

	~Sounds() = default;
private:
	sf::SoundBuffer m_soundBuffer[SOUND_FILES];
	sf::Sound m_sound[SOUND_FILES];	
	sf::Music m_music[MUSIC_FILES];			

};