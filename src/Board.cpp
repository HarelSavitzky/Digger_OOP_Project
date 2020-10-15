#include "Board.h"

//--------------------using Section --------------------
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::string;
using std::getline;
using std::istringstream;
using std::vector;

//default constructor------
Board::Board()
{}

//----------------------------------------build board functions ----------------------------------------
void Board::buildBoard(sf::RenderWindow& window, bool isFirst)
{
	static bool first = isFirst;
	if (first) 
	{
		setTextures();
		first = true;
	}																			//function to
	m_pixelSize.x = (window.getSize().x - FRAME_GAP) / getCols();			//build all the templet of the board
	m_pixelSize.y = (window.getSize().y - FRAME_GAP) / getRows();			//pictures/level blocking rectangle / and textures

	if (m_pixelSize.x < m_pixelSize.y)
		m_recPixelSize = m_pixelSize.x;	//setting the objects size according to input
	else
		m_recPixelSize = m_pixelSize.y;

	m_levelLimits.setSize(sf::Vector2f(m_recPixelSize * getCols(), m_recPixelSize * getRows()));
	m_levelLimits.setOrigin((m_recPixelSize * getCols()) / 2, (m_recPixelSize * getRows()) / 2);
	m_levelLimits.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	m_levelLimits.setOutlineThickness(12);
	m_levelLimits.setOutlineColor(sf::Color::Black);
	m_levelLimits.setFillColor(sf::Color::Transparent);


	m_backGround.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	m_backGround.setTexture(&m_backTex);
	m_backGround.setPosition(0, 0);


	for (int i = 0; i < GAME_MESSAGES; i++)
	{
		m_gameMessage[i].setSize(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
		if (i == GAME_OVER)
			m_gameMessage[i].setTexture(&m_gameMessageTex[GAME_OVER]);
		if (i == LOSE)
			m_gameMessage[i].setTexture(&m_gameMessageTex[LOSE]);
		if (i == WIN)
			m_gameMessage[i].setTexture(&m_gameMessageTex[WIN]);
		if (i == LEVEL_UP)
			m_gameMessage[i].setTexture(&m_gameMessageTex[LEVEL_UP]);
		if (i == QUIT)
			m_gameMessage[i].setTexture(&m_gameMessageTex[QUIT]);			
		m_gameMessage[i].setOrigin((sf::Vector2f((window.getSize().x / 2) / 2, (window.getSize().y / 2) / 2)));
		m_gameMessage[i].setPosition(window.getSize().x / 2, window.getSize().y / 2);
	}
}
//----------------------------------------draw functions ----------------------------------------
//draw messages------------------------------
void Board::drawGameMessage(sf::RenderWindow& window, int message)
{
	window.draw(m_gameMessage[message]);
}
//draw objects------------------------------
void Board::drawObjects(sf::RenderWindow& window)
{
	m_digger.draw(window);

	for (auto& StaticObjects : m_staticObjects)
		StaticObjects->draw(window);

	for (auto& Monsters : m_monsters)
		Monsters->draw(window);
}
//draw all board------------------------------
void Board::draw(sf::RenderWindow& window)
{
	window.draw(getBackground());
	window.draw(getLimits());
}

//----------------------------------------readStageFromFile functions ----------------------------------------
void Board::readStageFromFile(std::ifstream& gameFile, bool isFirst)
{
	std::string propertiesLine;							//function to read stage by stage
	std::string stringFromBoard;
	std::getline(gameFile, propertiesLine);

	if (!isFirst)								//if its not the first, read another row
		std::getline(gameFile, propertiesLine);	//(for the space row between stages)

	std::istringstream iss(propertiesLine);
	iss >> m_rows >> m_cols >> m_firstNumOfRocks >> m_time; //------read properties line
	m_startingTime = m_time;

	char trash;
	for (int z = 0; z < m_rows; z++)			//creates board representation in charcaters
	{
		std::vector < char >  t;
		for (int k = 0; k < m_cols; k++)
		{
			t.push_back(gameFile.get());
		}
		gameFile.get(trash);
		m_boardRepresentation.push_back(t);
	}
}

//--------------set textures----------------------------
void Board::setTextures()
{
	m_diggerTex.loadFromFile("alien.png");    \
	m_rockTex.loadFromFile("Rock.png");
	m_diamondTex.loadFromFile("redDiamond.png");
	m_stupidMonsterTex.loadFromFile("Monster.png");
	m_smartMonsterTex.loadFromFile("newSmart.png");
	m_wallTex.loadFromFile("wall.jpg");
	m_giftTex.loadFromFile("redChest.png");
	m_backTex.loadFromFile("boardback.jpg");

	m_gameMessageTex[GAME_OVER].loadFromFile("gameover.png");
	m_gameMessageTex[WIN].loadFromFile("win.png");
	m_gameMessageTex[LOSE].loadFromFile("lose.png");
	m_gameMessageTex[LEVEL_UP].loadFromFile("levelup.png");
	m_gameMessageTex[QUIT].loadFromFile("quit.png");
}

//----------------------------------------readObjectsFromFile function ----------------------------------------

void Board::readObjectsFromFile()
{
	srand(time(NULL));
	int kindOfMonster;
	countDiamods();
	sf::Vector2f levelSize(getCols(), getRows());
	for (int i = 0; i < m_boardRepresentation.size(); i++)					//build the SFML representation from the board representation
	{
		for (int j = 0; j < m_boardRepresentation[0].size(); j++)			//creating all objects---------------
		{
			sf::Vector2i objectIndex(i, j);
			char Symbol = m_boardRepresentation[i][j];
			switch (Symbol)
			{														
			case DIAMOND:
				m_staticObjects.emplace_back(std::make_unique<Diamond>(objectIndex, levelSize,
					m_diamondTex, DIAMOND, getLimits(), m_recPixelSize));
				break;
			case WALL:
				m_staticObjects.emplace_back(std::make_unique<Wall>(objectIndex, levelSize,
					m_wallTex, WALL, getLimits(), m_recPixelSize));
				break;
			case ROCK:
				m_staticObjects.emplace_back(std::make_unique<Rock>(objectIndex, levelSize,
					m_rockTex, ROCK, getLimits(), m_recPixelSize));
				break;
			case GIFT:
				m_staticObjects.emplace_back(std::make_unique<Gift>(objectIndex, levelSize,
					m_giftTex, GIFT, getLimits(), m_recPixelSize));
				break;
			case MONSTER:
				srand((99 * i) + j);			//srand(time(NULL));
				kindOfMonster = rand() % 2;
				switch (kindOfMonster)
				{
				case 0:
					m_monsters.emplace_back(std::make_unique<StupidMonster>(objectIndex, levelSize,
						m_stupidMonsterTex, MONSTER, getLimits(), m_recPixelSize, objectIndex));
					break;
				case 1:
					m_monsters.emplace_back(std::make_unique<SmartMonster>(objectIndex, levelSize,
						m_smartMonsterTex, MONSTER, getLimits(),  m_recPixelSize, objectIndex));
					break;
				}
				break;
			case DIGGER:
				m_digger = Digger{ objectIndex, levelSize, m_diggerTex, DIGGER , getLimits(),
					m_recPixelSize, objectIndex, m_firstNumOfRocks , m_firstNumOfDiamonds };
				break;
			}
		}
	}
}
//----------------------------------------check for cullusion function ----------------------------------------
sf::Keyboard::Key randKey()
{
	sf::Keyboard::Key key;
	int randNum = rand() % 4;
	switch (randNum)
	{
	case 0:
		key = KEYBOARD_UP;		//setting random key for random direction
		break;
	case 1:
		key = KEYBOARD_DOWN;
		break;
	case 2:
		key = KEYBOARD_RIGHT;
		break;
	case 3:
		key = KEYBOARD_LEFT;
		break;
	default: break;
	}
	return key;
}
void Board::checkForCollision(MovingObjects& object)
{
	for (int i = 0; i < m_staticObjects.size(); i++)
	{
		if (object.getSprite().getGlobalBounds().intersects(getStatics()[i]->getSprite().getGlobalBounds()))
		{
			object.handleCollision(*m_staticObjects[i]);
			if (object.getSymbol() == MONSTER && getStatics()[i]->getSymbol() == WALL)
				object.setDirection(randKey());			
			if (object.getSymbol() == MONSTER && getStatics()[i]->getSymbol() == ROCK)
				object.setDirection(randKey());
			if (object.getSymbol() == DIGGER && getStatics()[i].get()->getGotGift())		//loop to check monster || digger with statics
				randGift();
			if (object.getSymbol() == DIGGER && (getStatics()[i].get()->toDelete()))
				removeStatic(i);
		}
	}																				//function to check for collusion and send to double dispatch
	if (object.getSymbol() == DIGGER)								
	{
		for (int i = 0; i < getMonsters().size(); i++)
		{
			if (object.getSprite().getGlobalBounds().intersects(
				getMonsters()[i]->getSprite().getGlobalBounds()))
			{
				object.handleCollision(*getMonsters()[i]);			//loop to check digger with monster
				if (getDigger().diggerDead())
					setMovingStartingLocation();
			}
		}
	}
	if (object.getSymbol() == MONSTER)
	{
		for (int i = 0; i < getMonsters().size(); i++)
		{
			if (getDigger().getSprite().getGlobalBounds().intersects(	//loop to check monster with digger
				getMonsters()[i]->getSprite().getGlobalBounds()))
			{
				object.handleCollision(getDigger());
				if (getDigger().diggerDead())
					setMovingStartingLocation();
			}
		}
	}
}
//-----------------------------randomize gift function ------------------------------
void Board::randGift()
{
	int randNum = rand() % 3;
	switch (randNum)
	{
	case 0:
		getDigger().increaseScore(GIFT_SCORE);		
		m_giftScore++;
		m_giftToDraw = SCORE_MESSAGE;
		break;
	case 1:
		getDigger().increaseRocks();
		m_giftToDraw = ROCK_MESSAGE;
		break;
	case 2:
		setTime(GIFT_TIME);
		m_giftToDraw = TIME_MESSAGE;
		break;
	}
}


//-----------------------------setMovingStartingLocation function ------------------------------
void Board::setMovingStartingLocation()
{
	m_digger.getSprite().setPosition((((WINDOW_WIDTH / 2) - ((getCols() * m_recPixelSize) / 2)) +
		(m_digger.getStartingPoint().y * m_recPixelSize)),
		((WINDOW_HEIGHT / 2) - ((getRows() * m_recPixelSize) / 2)) + 
		(m_digger.getStartingPoint().x * m_recPixelSize));								//function to reset movables to first position

	for (int i = 0; i < m_monsters.size(); i++)
		m_monsters[i].get()->getSprite().setPosition((((WINDOW_WIDTH / 2) - ((getCols() * m_recPixelSize) / 2)) +
		(m_monsters[i]->getStartingPoint().y * m_recPixelSize)),
			((WINDOW_HEIGHT / 2) - ((getRows() * m_recPixelSize) / 2))
			+ (m_monsters[i]->getStartingPoint().x * m_recPixelSize));
}
//-----------------------------set/reset  functions ------------------------------
//-----------------------------countDiamods  functions ------------------------------

void Board::countDiamods()
{
	m_firstNumOfDiamonds = 0;
	for (int i = 0; i < m_boardRepresentation.size(); i++)
	{
		for (int j = 0; j < m_boardRepresentation[0].size(); j++)
		{
			char Symbol = m_boardRepresentation[i][j];
			switch (Symbol)
			{
			case DIAMOND:
				m_firstNumOfDiamonds += 1; break;
			default:break;
			}
		}
	}
}
//------------------------------------------------
void Board::resetGiftScoreNum()
{
	m_giftScore = 0;
}

//------------------------------------------------
void Board::resetGiftToDraw()
{
	m_giftToDraw = NO_GIFT;
}
//------------------------------------------------
void Board::setTime(int time)
{
	m_time += time;
}
//------------------------------------------------
void Board::resetTime()
{
	m_time = m_startingTime;
}
//------------------------------------------------
void Board::decreaseTime()
{
	m_time--;
}
//-----------------------------remove  functions ------------------------------
void Board::removeStatic(int index)		
{
	m_staticObjects.erase(m_staticObjects.begin() + index);
}
//-----------------------------remove  functions ------------------------------
void Board::clearVectors()
{
	m_staticObjects.clear();
	m_monsters.clear();
}

//----------------------------------------get functions ----------------------------------------
//----------------------------------------get Objects functions ----------------------------------------

Digger& Board::getDigger()
{
	return m_digger;
}

std::vector < std::unique_ptr <Monster>>& Board::getMonsters()
{
	return m_monsters;
}
std::vector < std::unique_ptr <StaticObjects>>& Board::getStatics()
{
	return m_staticObjects;
}
//----------------------------------------get members functions ----------------------------------------
int Board::getGiftScore() const
{
	return m_giftScore;
}
//------------------------------------------------
int Board::getRows() const
{
	return m_rows;
}
//------------------------------------------------
int Board::getCols() const
{
	return m_cols;
}
//------------------------------------------------
int Board::getNumOfRocksAllowed() const
{
	return m_firstNumOfRocks;
}
//------------------------------------------------
int Board::getTime() const
{
	return m_time;
}
//------------------------------------------------
sf::RectangleShape Board::getLimits() const
{
	return m_levelLimits;
}
//------------------------------------------------
sf::RectangleShape Board::getBackground() const
{
	return m_backGround;
}
//------------------------------------------------

sf::Vector2f Board::getPixelSize() const
{
	return m_pixelSize;
}
//------------------------------------------------
int Board::getStartingTime() const
{
	return m_startingTime;
}
//------------------------------------------------
std::vector <std::vector < char > > Board::getBoardRepresentation() const
{
	return m_boardRepresentation;
}
//------------------------------------------------
int Board::getGiftToDraw() const
{
	return m_giftToDraw;
}