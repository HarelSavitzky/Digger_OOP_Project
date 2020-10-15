#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib> 
#include <stdlib.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Sounds.h"
#include "StaticObjects.h"
#include "MovingObjects.h"
#include "Wall.h"
#include "Rock.h"
#include "Diamond.h"
#include "Gift.h"
#include "Digger.h"
#include "Monster.h"
#include "StupidMonster.h"
#include "SmartMonster.h"

//--------------------Board Class --------------------

class Board
{
public:
	Board(); //default constructor
		//--------------------class functions --------------------

		//building + reading + setting functions-----------------
	void buildBoard(sf::RenderWindow& window, bool isFirst);
	void readStageFromFile(std::ifstream& gameFile, bool isFirst);
	void readObjectsFromFile();

	void setTextures();
	void setMovingStartingLocation();

		//initializing members for overwrite-------
	void clearBoardRepresentation() { m_boardRepresentation.clear(); }
	void clearVectors();
	void removeStatic(int index);

	void countDiamods();
	void setTime(int time);
	void decreaseTime();
	void resetTime();

			//gift handling functions-----
	void resetGiftToDraw();
	void randGift();
	void resetGiftScoreNum();
			
		//checks for collusion -> than double dispatch
	void checkForCollision(MovingObjects& object);
		
		//getting object members functions-----
	Digger& getDigger();
	std::vector < std::unique_ptr <Monster>>& getMonsters();
	std::vector < std::unique_ptr <StaticObjects>>& getStatics();
			
				//get functions---------------
	std::vector <std::vector < char > > getBoardRepresentation() const;
	sf::RectangleShape getLimits() const;
	sf::RectangleShape getBackground() const;
	sf::Vector2f getPixelSize() const;
	int getTime() const;
	int getRows() const;
	int getCols() const;
	int getNumOfRocksAllowed() const;
	int getGiftScore() const;
	int getStartingTime() const;
	int getGiftToDraw() const;
				
			//draw functions-----------
	void draw(sf::RenderWindow& window);	//draw the board templet
	void drawObjects(sf::RenderWindow& window);//draw the objects
	void drawGameMessage(sf::RenderWindow& window, int message);//draw the game messages

	~Board() = default;

private:
	//object members---------------
	std::vector < std::unique_ptr <StaticObjects>> m_staticObjects;
	std::vector < std::unique_ptr <Monster>> m_monsters;
	Digger m_digger;

	std::vector <std::vector < char > > m_boardRepresentation;	

		//textures--------------
	sf::Texture m_gameMessageTex[GAME_MESSAGES];
	sf::Texture m_diggerTex;
	sf::Texture m_stupidMonsterTex;
	sf::Texture m_smartMonsterTex;
	sf::Texture m_diamondTex;
	sf::Texture m_rockTex;
	sf::Texture m_wallTex;
	sf::Texture m_giftTex;
	sf::Texture m_backTex;
		//rectangles--------------
	sf::RectangleShape m_gameMessage[GAME_MESSAGES];
	sf::RectangleShape m_backGround;

	sf::RectangleShape m_levelLimits; //game bounds

	//object size according to input
	sf::Vector2f m_pixelSize;	//X Y size
	float m_recPixelSize;	//square size

	//int members-----------
	int m_rows;
	int m_cols;
	int	m_firstNumOfRocks;
	int m_firstNumOfDiamonds;
	int m_time;
	int m_startingTime;
	int m_giftScore = 0;
	int m_giftToDraw = NO_GIFT;
	//bool members----------
	bool m_isDead;
	bool m_monsterStopped;
};