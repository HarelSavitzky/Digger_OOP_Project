#pragma once
//--------------------include Section --------------------
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib> 
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <ostream>
#include <iterator>
#include <windows.h>
#include "Text.h"
#include "Board.h"
#include "Menu.h"
#include "Const.h"
#include "Sounds.h"

//--------------------GameManager Class --------------------
class GameManager
{
public:
	GameManager(); //default constructor
	//--------------------class functions --------------------

	void manageGame();	//main managing function
									
	void inMenuFunc(sf::Event& event, sf::RenderWindow& m_window,	//function to handle menu
		Menu& m_menu, std::ifstream& gameFile);

	void createStage(sf::RenderWindow& m_window, std::ifstream& gameFile);	//function to creat first or next stage
	void restartGame(sf::RenderWindow& m_window, std::ifstream& gameFile);	//restrt entire game func
	void restartLevel(sf::RenderWindow& m_window);	//restart level func

	void checkPlayerStatus(sf::RenderWindow& m_window,std::ifstream& gameFile);//check player current stat in game
	void updateStats();	// update stats

	void handleDiggerMovement(sf::Event event);	//handle movement
	void handleMonstersMovement();

	void openClocks();	//clock opening + handle
	void checkGameTime();
								//game presentation-audio+graphics
	void presentGame(sf::RenderWindow& m_window, std::ifstream& gameFile, Menu& m_menu);

			//function to handle different cases that need to be managed
	void handleGifts(sf::RenderWindow& m_window);
	void endGameHandle(sf::RenderWindow& m_window, std::ifstream& gameFile);
	void checkIfTime();
	void ifMetMonster();
	void ifAteRock();
	void ifAteDiamond();
	void playerDied();
	void diggerEaten();
	void startPressed();
	void quitPressed(sf::RenderWindow& m_window, std::ifstream& gameFile);

	Board& getBoard();
	void openFile(std::ifstream& gameFile);	

private: 
	Board m_board;
	Sounds m_sound;
	Text m_gameText;

	sf::Clock m_clock;

	//timers
	sf::Time m_deltaTime;
	sf::Time m_gameDeltaTime;
	sf::Time m_monsterTime;
	sf::Time m_giftClock;

	int m_currentStats[GAME_STATS];	//current stats
	int m_gameTime;//game timer
	int m_currentLevelScore;//not for stats - but for level reset of score -need another one....
	int m_levelCounter = 1;

	//bool section-----------------------
	bool m_endProgram = false;
	bool m_isFirst = true;
	bool m_inMenu = true;
	bool m_gameStarted;
	bool m_startClock;
	bool m_gameOver = false;
	bool m_playerDied = false;
	bool m_wonGame = false;
	bool m_levelUp = false;
	bool m_eatenByMonster = false;

};