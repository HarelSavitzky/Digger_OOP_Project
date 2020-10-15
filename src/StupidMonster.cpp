#include "StupidMonster.h"
#include "GameManager.h"

StupidMonster::StupidMonster()
{}
//---------------------setDirection function --------------------------
void StupidMonster::setDirection(GameManager& manager, sf::Time deltaTime) //change to delta time sf::time
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
	setDeltaTime(deltaTime);

	MovingObjects::setDirection(key);
}
//---------------------virtual functions --------------------------
bool StupidMonster::diggerDead()
{
	return m_isDead;
}
//---------------------souble dispatch function --------------------------
void StupidMonster::handleCollision(Objects& object)
{
	object.handleCollision(*this);
}
//--------------------
void StupidMonster::handleCollision(Digger& digger)
{
	digger.decreaseLife();	//kills
	m_isDead = true;
}
//---------------------
void StupidMonster::handleCollision(Wall& wall)
{
	MovingObjects::stopObject();
}
//---------------------
void StupidMonster::handleCollision(Rock& rock)//blocked
{
	MovingObjects::stopObject();
}
//---------------------
void StupidMonster::handleCollision(Diamond& diamond){}
void StupidMonster::handleCollision(Gift& gift){}
void StupidMonster::handleCollision(SmartMonster& smartMonster){}
void StupidMonster::handleCollision(StupidMonster& stupidMonster){}