//--------------------include Section --------------------
#include "Digger.h"
#include <iostream>
#include "GameManager.h"

//--------------------constructor  --------------------
Digger::Digger(sf::Vector2i objectIndex, sf::Vector2f levelSize, sf::Texture& texture,
	char Symbol, sf::RectangleShape limitRec, float pixelSize, sf::Vector2i startingPoint, int numOfRocks,
	int numOfDiamonds) : MovingObjects(objectIndex, levelSize, texture,
	Symbol, limitRec, pixelSize, startingPoint)
{
	m_firstNumOfDiamonds = numOfDiamonds;		
	m_firstNumOfRocks = numOfRocks;
	m_numOfDiamonds = numOfDiamonds;
	m_numOfRocks = numOfRocks;

	m_score = STARTING_SCORE;
	m_lifes = STARTING_LIFES;
}
//--------------------using Section --------------------

void Digger::resetMembers(int numOfRocks, int score, int lifes)
{
	m_numOfDiamonds = m_firstNumOfDiamonds;				
	m_numOfRocks = numOfRocks;
	m_score = score;
	m_lifes = lifes;					
}

//----------------------------------------set functions ----------------------------------------
//----------------------------------------
void Digger::increaseScore(int score)
{
	m_score += score;			
}
//----------------------------------------
void Digger::decreaseRocks()
{
	m_numOfRocks -= 1;
}
//----------------------------------------
void Digger::increaseRocks()
{
	m_numOfRocks += 1;
}
//----------------------------------------
void Digger::decreaseLife()
{
	m_lifes -= 1;
}
//----------------------------------------
void Digger::setLife(int life)
{
	m_lifes = life;
}
//---------------------------------------
void Digger::decreaseDiamonds()
{
	m_numOfDiamonds-=1;
}
//----------------------------------------
bool Digger::getGotGift()
{
	return m_gotAGift;
}
//----------------------------------------
//----------------------------------------set direction func ------------------
void Digger::setDirection(sf::Keyboard::Key key, GameManager& manager, sf::Time deltaTime)
{
	setDeltaTime(deltaTime);
	if (!inGameBounds(key))		//if in game bounds
		MovingObjects::setDirection(sf::Keyboard::Key::Space);// set space means dont move
	else
		MovingObjects::setDirection(key);

	MovingObjects::move(getDirection(), deltaTime);

	manager.getBoard().checkForCollision(*this);	//check collision
}
//----------------------------------------get functions ----------------------------------------
//----------------------------------------
int Digger::getNumOfRocks() const
{
	return m_numOfRocks;
}
//---------------------------------------
int Digger::getScore() const
{
	return m_score;
}
//----------------------------------------
int Digger::getLife() const
{
	return m_lifes;
}
//----------------------------------------
int Digger::getStartingDiamonds() const
{
	return m_firstNumOfDiamonds;
}
//----------------------------------------
int Digger::getDiamondsToWin() const
{
	return m_numOfDiamonds;
}
//----------------------------------------
//-----------------------------virtual func ------------------

bool Digger::toDelete()
{
	return m_toDelete;
}
//----------------------------------------
bool Digger::diggerDead()
{
	return m_isDead;
}
//---------------double dispatch functions--------------------
void Digger::handleCollision(Objects& object)
{
	object.handleCollision(*this);
}
//----------------------------------------
void Digger::handleCollision(SmartMonster& smartMonster)
{
	decreaseLife();
	m_isDead = true;
}
//----------------------------------------
void Digger::handleCollision(StupidMonster& stupidMonster)	//monsters decrease life and report death
{
	decreaseLife();
	m_isDead = true;
}
//----------------------------------------
void Digger::handleCollision(Wall& wall)
{
	MovingObjects::stopObject();		//wall blocks
}
//----------------------------------------
void Digger::handleCollision(Rock& rock)
{
	decreaseRocks();					//rock blocks&deleted
	m_toDelete = true;
}
//----------------------------------------
void Digger::handleCollision(Diamond& diamond)
{
	increaseScore(DIAMOND_SCORE);			//diamond score +delete
	decreaseDiamonds();
	m_toDelete = true;
}
//----------------------------------------
void Digger::handleCollision(Gift& gift)
{
	m_gotAGift = true;						//report gift and delete
	m_toDelete = true;
}
//----------------------------------------
void Digger::handleCollision(Digger& digger) {}
