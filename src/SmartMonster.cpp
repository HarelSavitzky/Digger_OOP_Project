#include "SmartMonster.h"
#include "GameManager.h"

SmartMonster::SmartMonster()
{}
//---------------------setDirection function --------------------------
void SmartMonster::setDirection(GameManager& manager, sf::Time deltaTime)
{
	static sf::Keyboard::Key key = KEYBOARD_SPACE;

	sf::Vector2f diggerLocation = manager.getBoard().getDigger().getSprite().getPosition();
	float x = diggerLocation.x - this->getSprite().getPosition().x;
	float y = diggerLocation.y - this->getSprite().getPosition().y;

	if (abs(y) < abs(x))
	{
		if (x < 0)
			key = KEYBOARD_LEFT;		//set the direction acording to the absolute distance
		else
			key = KEYBOARD_RIGHT;		//from the digger
	}
	else
	{
		if (y < 0)
			key = KEYBOARD_UP;
		else
			key = KEYBOARD_DOWN;
	}
	setDeltaTime(deltaTime);
	MovingObjects::setDirection(key);	//use set direction ogf moveable to determine direction
}											//to pervent 4 times the code
//---------------------virtual function --------------------------
bool SmartMonster::diggerDead()
{
	return m_isDead;
}
//---------------------double dispatch functions --------------------------
void SmartMonster::handleCollision(Objects& object)
{
	object.handleCollision(*this);
}
//--------------------
void SmartMonster::handleCollision(Digger& digger)
{
	digger.decreaseLife();	//kills
	m_isDead = true;
}
//---------------------
void SmartMonster::handleCollision(Wall& wall)
{
	MovingObjects::stopObject();
}
//---------------------
void SmartMonster::handleCollision(Rock& rock)	//blocked
{
	MovingObjects::stopObject();
}
//---------------------
void SmartMonster::handleCollision(Diamond& diamond){}
void SmartMonster::handleCollision(Gift& gift){}
void SmartMonster::handleCollision(SmartMonster& smartMonster){}
void SmartMonster::handleCollision(StupidMonster& stupidMonster){}