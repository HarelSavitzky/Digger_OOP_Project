#pragma once
//--------------------include Section --------------------
#include "MovingObjects.h"

//--------------------Monster Class definition --------------------
class Monster : public MovingObjects
{
public:
	using MovingObjects::MovingObjects;
	Monster();

	//--------------------Virtuals --------------------
	virtual void setDirection(GameManager& manager, sf::Time deltaTime) = 0;

	virtual void handleCollision(Objects& object) = 0;
	virtual void handleCollision(SmartMonster& smartMonster) = 0;
	virtual void handleCollision(StupidMonster& stupidMonster) = 0;
	virtual void handleCollision(Digger& digger) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(Rock& rock) = 0;
	virtual void handleCollision(Diamond& diamond) = 0;
	virtual void handleCollision(Gift& gift) = 0;

private:

};