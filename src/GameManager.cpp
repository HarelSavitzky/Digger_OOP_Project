#include "GameManager.h"


GameManager::GameManager()
{}
//----------------------------------------main manager function ----------------------------------------
void GameManager::manageGame()
{
	std::ifstream gameFile;	
	openFile(gameFile);

	srand(time(NULL));

	sf::RenderWindow m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Digger - Savitzky Ltd.");
	sf::Event event;
	Menu m_menu(m_window.getSize().x, m_window.getSize().y);
	sf::Clock m_clock;											//different variable definition
															//----------------------------------
	createStage(m_window, gameFile);		//create stage

	while (m_window.isOpen() && (!m_endProgram))				//main game/event loops, runs until bool false
	{
		while (m_window.pollEvent(event) && (!m_endProgram))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();		//close window event
				break;

			case sf::Event::KeyReleased:	//in menu event
				if (m_inMenu)
					inMenuFunc(event, m_window, m_menu, gameFile);
				else
					event.key.code = KEYBOARD_SPACE;	//conditions so unpress wont effect alien
				break;
			}
		}
		if (!m_inMenu)					//if not on menu -> in game
		{
			handleDiggerMovement(event);
			openClocks();
			checkPlayerStatus(m_window, gameFile);		//if died? if won?.......
			checkGameTime();
			handleMonstersMovement();
			updateStats();
		}
		presentGame(m_window, gameFile, m_menu);	//present the game
	}
}
//---------------------inMenuFunc function --------------------------
void GameManager::inMenuFunc(sf::Event& event,
	sf::RenderWindow& m_window, Menu& m_menu, std::ifstream& gameFile)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		m_menu.MoveUp();	
		break;
									//move up and down in menu
	case sf::Keyboard::Down:
		m_menu.MoveDown();
		break;

	case sf::Keyboard::Return:				//enter pressed
		switch (m_menu.getPressedItem())
		{
		case 0:
			startPressed();			//on play
			break;
		case 1:
			quitPressed(m_window, gameFile);	//on quit
			break;
		}
	}
}
//---------------------quitPressed function --------------------------
void GameManager::quitPressed(sf::RenderWindow& m_window, std::ifstream& gameFile)
{
	m_window.clear();
	m_board.drawGameMessage(m_window, QUIT);
	m_window.display();
	Sleep(2000);										//close relevant and
	m_sound.stopMusic(MENU_MUSIC);				//finish all the program
	gameFile.close();
	m_window.close();
	m_endProgram = true;
}
//---------------------startPressed function --------------------------
void GameManager::startPressed()
{
	m_inMenu = false;
	m_gameStarted = true;					//-initiate the game 

	m_sound.stopMusic(MENU_MUSIC);
	m_sound.startMusic(GAME_MUSIC, GAME_VOLUME);
}

//---------------------presentGame function --------------------------
void GameManager::presentGame(sf::RenderWindow& m_window,
	std::ifstream& gameFile, Menu& m_menu)
{
	if (m_inMenu)
		m_menu.draw(m_window);
	else
	{
		m_board.draw(m_window);
		m_gameText.draw(m_window);				//function to
		m_board.drawObjects(m_window);		//play the game acording to whats happening
												//draw and sound
		if (m_gameOver)
			endGameHandle(m_window, gameFile);
		if (m_levelUp)
			createStage(m_window, gameFile);
		if (m_playerDied)
			playerDied();
		if (m_eatenByMonster)
			diggerEaten();
		if (m_wonGame)
			endGameHandle(m_window, gameFile);

		handleGifts(m_window);
	}
	m_window.display();
}
//---------------------endGameHandle function --------------------------
void GameManager::endGameHandle(sf::RenderWindow& m_window, std::ifstream& gameFile)
{
	if (m_wonGame)
	{
		m_board.drawGameMessage(m_window, WIN);
		m_sound.playSound(WON_GAME_SOUND);		//won
		m_wonGame = false;
	}
	else
	{
		m_board.drawGameMessage(m_window, GAME_OVER);		//lost
		m_sound.playSound(LOST_GAME_SOUND);
		m_gameOver = false;
	}
	m_window.display();
	Sleep(3500);
	m_inMenu = true;			//back to menu
	m_gameStarted = false;
	restartGame(m_window, gameFile);
	m_sound.stopMusic(GAME_MUSIC);
	m_sound.startMusic(MENU_MUSIC, MENU_VOLUME);
}

//---------------------restartGame function --------------------------
void GameManager::restartGame(sf::RenderWindow& m_window, std::ifstream& gameFile)
{
	m_window.clear();
	m_board.clearVectors();
	m_isFirst = true;
	m_levelCounter = 1;								//restart the game to first level
	gameFile.clear();
	gameFile.seekg(0);
	m_board.clearBoardRepresentation();
	createStage(m_window, gameFile);
}
//---------------------createStage function --------------------------
void GameManager::createStage(sf::RenderWindow& m_window, std::ifstream& gameFile)
{
	if (!m_isFirst)
	{
		m_sound.playSound(FINISH_LEVEL_SOUND);				//if not the first stage
		m_board.drawGameMessage(m_window, LEVEL_UP);
		m_window.display();					//display level up
		Sleep(2000);
		m_levelUp = false;				
		m_levelCounter++;			//level counter update
		m_currentStats[LEVEL] = m_levelCounter;
		m_board.getDigger().increaseScore(LEVEL_SCORE);
		m_currentStats[SCORE] = m_board.getDigger().getScore();
		m_currentStats[LIFE] = m_board.getDigger().getLife();	//keep relevant stats
		m_board.clearVectors();
		m_board.clearBoardRepresentation();	//clean relevant board members
		m_gameStarted = true;
	}
	m_board.readStageFromFile(gameFile, m_isFirst);
	m_board.buildBoard(m_window, m_isFirst);		//things that happan in first level and also in next
	m_board.readObjectsFromFile();
	m_currentStats[DIAMONDS] = m_board.getDigger().getDiamondsToWin();
	checkIfTime();

	if (m_isFirst)
	{
		m_gameText.buildInfoBars();					//only on first level
		m_sound.defineSound();
		m_sound.startMusic(MENU_MUSIC, MENU_VOLUME);
		m_gameText.initializeStats(STARTING_SCORE, 99, m_board.getDigger().getNumOfRocks(),
			STARTING_LIFES, m_currentStats[LEVEL]);
	}
	else
	{
		m_board.getDigger().increaseScore(m_currentStats[SCORE]);		//happans in next...
		m_board.getDigger().setLife(m_currentStats[LIFE]);
	}
	m_gameText.initializeStats(m_board.getDigger().getScore(), m_board.getTime(),
		m_board.getDigger().getNumOfRocks(),
		m_board.getDigger().getLife(), m_currentStats[LEVEL]);
	updateStats();
}
//---------------------restartLevel function --------------------------
void GameManager::restartLevel(sf::RenderWindow& m_window)
{
	m_window.clear();
	m_board.resetTime();									//restart  current level
	m_board.clearVectors();
	m_currentLevelScore = (m_board.getDigger().getStartingDiamonds()
		- m_board.getDigger().getDiamondsToWin()) * DIAMOND_SCORE;
	m_board.readObjectsFromFile();
	m_board.getDigger().resetMembers(m_board.getDigger().getNumOfRocks(),
		m_currentStats[SCORE] - m_currentLevelScore - (m_board.getGiftScore() * GIFT_SCORE),
		m_currentStats[LIFE]); 
	m_board.resetGiftScoreNum();
	updateStats();
}
//---------------------updateStats function --------------------------
void GameManager::updateStats()
{
	m_gameText.setSpecificStat(SCORE, m_board.getDigger().getScore());
	m_gameText.setSpecificStat(LIFE, m_board.getDigger().getLife());		//update text stats on screen
	m_gameText.setSpecificStat(ROCKS, m_board.getDigger().getNumOfRocks());
	m_gameText.setTime(m_board.getTime());
	m_gameText.setSpecificStat(LEVEL, m_levelCounter);

	m_currentStats[SCORE] = m_board.getDigger().getScore();	//update current stats -always compared with last
	m_currentStats[ROCKS] = m_board.getDigger().getNumOfRocks();
	m_currentStats[TIME] = m_board.getTime();
	m_currentStats[LEVEL] = m_levelCounter;

	m_currentStats[LIFE] = m_board.getDigger().getLife();
}

//---------------------checkPlayerStatus function --------------------------
void GameManager::checkPlayerStatus(sf::RenderWindow& m_window,
	std::ifstream& gameFile)
{
	if (m_board.getDigger().getLife() == 0)		//if died
		m_gameOver = true;

	if (m_board.getDigger().getNumOfRocks() < 0 || m_board.getTime() == 0)	//if ate too much rocks or ran out of time
	{
		m_board.getDigger().decreaseLife();
		m_currentStats[LIFE] = m_board.getDigger().getLife();
		m_playerDied = true;
		restartLevel(m_window);			//start over
	}
	if (m_board.getDigger().getDiamondsToWin() == 0)	//if won
	{
		if (gameFile.eof())
		{
			m_wonGame = true;
			m_levelUp = false;
		}
		else
		{
			m_levelUp = true;
			m_isFirst = false;
		}
	}
}
//---------------------handleDiggerMovement function --------------------------
void GameManager::handleDiggerMovement(sf::Event event)
{
	m_board.getDigger().setDirection(event.key.code, *this, m_deltaTime);
	ifMetMonster();
	ifAteRock();	//if this stuff happand on movement- make a sound
	ifAteDiamond();
}

//---------------------handleMonstersMovement function --------------------------
void GameManager::handleMonstersMovement()
{
	if (m_monsterTime.asSeconds() >= rand() % 2+1)			//set new direction each 2 seconds
	{
		for (int i = 0; i < m_board.getMonsters().size(); i++)
		{
			m_board.getMonsters()[i]->setDirection(*this, m_deltaTime);
		}
		m_monsterTime = sf::seconds(0.0);
	}
	for (int i = 0; i < m_board.getMonsters().size(); i++)		//allways move
	{
		m_board.getMonsters()[i]->move(m_board.getMonsters()[i]->getDirection(), m_deltaTime);

		m_board.checkForCollision(*m_board.getMonsters()[i]);

		if (!m_board.getMonsters()[i]->inGameBounds(m_board.getMonsters()[i]->getKey()))	//only in game bounds
			m_board.getMonsters()[i]->setDirection(*this, m_deltaTime);
	}
	ifMetMonster();
}
//------------------------------------if  happand in digger movement functions------------------------------------
//---------------------ifMetMonster function --------------------------
void GameManager::ifMetMonster()
{
	if (m_currentStats[LIFE] != m_board.getDigger().getLife())//if current stat didnt updated yet
	{														//it means ate an onject, do relevant sound
		m_eatenByMonster = true;
		m_currentStats[LIFE] = m_board.getDigger().getLife();
	}
}
//---------------------ifAteRock function --------------------------
void GameManager::ifAteRock()
{
	if (m_currentStats[ROCKS] > m_board.getDigger().getNumOfRocks())	//if current stat didnt updated yet
	{																		//it means ate an onject, do relevant sound
		m_currentStats[ROCKS] != m_board.getDigger().getNumOfRocks();
		m_sound.playSound(EAT_ROCK_SOUND);
	}
}
//---------------------ifAteDiamond function --------------------------
void GameManager::ifAteDiamond()
{
	if (m_currentStats[DIAMONDS] > m_board.getDigger().getDiamondsToWin())		//if current stat didnt updated yet
	{																			//it means ate an onject, do relevant sound
		m_currentStats[DIAMONDS] = m_board.getDigger().getDiamondsToWin();
		m_sound.playSound(EAT_DIAMOND_SOUND);
	}
}
//---------------------diggerEaten function --------------------------
void GameManager::diggerEaten()
{
	m_sound.playSound(MET_MONSTER_SOUND);
	Sleep(500);
	m_eatenByMonster = false;
	m_currentStats[LIFE] = m_board.getDigger().getLife();
	m_board.resetTime();
}
//---------------------playerDied function --------------------------
void GameManager::playerDied()
{
	m_sound.playSound(LEVEL_FAILED_SOUND);
	Sleep(2000);
	m_playerDied = false;
	m_gameStarted = true;
}
//---------------------handle gifts function --------------------------
//to handle gift sound and text-----------------
void GameManager::handleGifts(sf::RenderWindow& m_window)
{
	if (m_board.getGiftToDraw() != NO_GIFT)
	{
		if (m_giftClock <= sf::seconds(0.01))	//so sound wont play in super fast loop
			m_sound.playSound(GIFT_SOUND);

		m_giftClock += m_deltaTime;
		if (m_board.getGiftToDraw() == SCORE_MESSAGE)
			m_gameText.drawGiftMessage(m_window, SCORE_MESSAGE);
		if (m_board.getGiftToDraw() == ROCK_MESSAGE)
			m_gameText.drawGiftMessage(m_window, ROCK_MESSAGE);
		if (m_board.getGiftToDraw() == TIME_MESSAGE)
			m_gameText.drawGiftMessage(m_window, TIME_MESSAGE);

		if (m_giftClock >= sf::seconds(1.2))		//drawmessage  for certain time
		{
			m_board.resetGiftToDraw();
			m_giftClock = sf::seconds(0.0);
		}
	}
}
//------------------------------------ time handle functions------------------------------------
//---------------------checkIfTime function --------------------------
void GameManager::checkIfTime()
{
	if (m_board.getTime() == -1)	//if theres no time limit for level
		m_startClock = false;
	else
		m_startClock = true;
}
//---------------------checkGameTime function --------------------------
void GameManager::checkGameTime()
{
	m_monsterTime += m_deltaTime;
	if (m_startClock == true)
	{

		m_gameDeltaTime += m_deltaTime;			//count timers and game time

		if (m_gameDeltaTime.asSeconds() >= 1)
		{
			m_board.decreaseTime();
			m_gameDeltaTime = sf::seconds(0);
		}
	}
	m_deltaTime = m_clock.restart();
}
//---------------------openClocks function --------------------------
void GameManager::openClocks()
{
	if (m_gameStarted)
	{												//out of menu?
		m_deltaTime = m_clock.restart();		//start the clocks
		m_gameDeltaTime += m_deltaTime;
		m_gameStarted = false;
	}
}

//------------------------------------------different functions ----------------------------------------------------
//---------------------getBoard function --------------------------

Board& GameManager::getBoard()
{
	return m_board;
}
//---------------------openFile function --------------------------
void GameManager::openFile(std::ifstream& gameFile)
{
	gameFile.open("Board.txt");					//function to open the game file
	if (!gameFile.is_open())
	{
		std::cerr << "ERROER\n";
		exit(EXIT_FAILURE);
	}
}