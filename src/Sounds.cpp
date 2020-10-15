#include "Sounds.h"

Sounds::Sounds()
{}
//---------------------defineSound function --------------------------
void Sounds::defineSound()
{
for (int i = 0; i < MUSIC_FILES; i++)		
	{
		if(i == MENU_MUSIC)
			m_music[i].openFromFile("MenuMusic.ogg");
		else
			m_music[i].openFromFile("ingamemusic.wav");
	}

	for (int i = 0; i < SOUND_FILES; i++)		//loading file to buffers and buffers to sounds
	{
		if (i == MET_MONSTER_SOUND)
		{
			m_soundBuffer[i].loadFromFile("scream.wav");
			m_sound[i].setBuffer(m_soundBuffer[i]);
			m_sound[i].setVolume(35);
		}
		if (i == EAT_ROCK_SOUND)
		{
			m_soundBuffer[i].loadFromFile("eat.wav");
			m_sound[i].setBuffer(m_soundBuffer[i]);
		}
		if (i == EAT_DIAMOND_SOUND)
		{
			m_soundBuffer[i].loadFromFile("collectedDiamond.wav");
			m_sound[i].setBuffer(m_soundBuffer[i]);
		}
		if (i == LEVEL_FAILED_SOUND)
		{
			m_soundBuffer[i].loadFromFile("levelfailed.wav");
			m_sound[i].setBuffer(m_soundBuffer[i]);
			m_sound[i].setVolume(30);
		}
		if (i == FINISH_LEVEL_SOUND)
		{
			m_soundBuffer[i].loadFromFile("levelUp.wav");	
			m_sound[i].setBuffer(m_soundBuffer[i]);
		}
		if (i == START_LEVEL_SOUND)
		{
			m_soundBuffer[i].loadFromFile("startlevel.wav");
			m_sound[i].setBuffer(m_soundBuffer[i]);
		}
		if (i == WON_GAME_SOUND)
		{
			m_soundBuffer[i].loadFromFile("WonGame.wav");
			m_sound[i].setBuffer(m_soundBuffer[i]);
		}
		if (i == LOST_GAME_SOUND)
		{
			m_soundBuffer[i].loadFromFile("lostGame.wav");
			m_sound[i].setBuffer(m_soundBuffer[i]);
		}		
		if (i == GIFT_SOUND)
		{
			m_soundBuffer[i].loadFromFile("chest.wav");
			m_sound[i].setBuffer(m_soundBuffer[i]);
		}
	}
}
//---------------------startMusic function --------------------------
void Sounds::startMusic(int music, int volume)
{
	m_music[music].setLoop(true);		//function to start music
	m_music[music].setVolume(volume);
	m_music[music].play();
}
//---------------------stopMusic function --------------------------
void Sounds::stopMusic(int music)	//function to stop it
{
	m_music[music].stop();
}
//---------------------playSound function --------------------------
void Sounds::playSound(int sound)	//function to play a sound
{
	m_sound[sound].play();
}