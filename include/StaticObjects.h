#pragma once
//--------------------include Section --------------------
#include "Objects.h"
#include "Digger.h"
#include "Monster.h"

//--------------------Static Objects Class definition --------------------
class StaticObjects : public Objects
{
public:
	using Objects::Objects;
	StaticObjects();

	//--------------------Virtuals --------------------
	virtual void draw(sf::RenderWindow& window);
	virtual bool toDelete();
	virtual bool getGotGift();

	virtual void handleCollision(Objects& object) = 0;
	virtual void handleCollision(SmartMonster& smartMonster) = 0;
	virtual void handleCollision(StupidMonster& stupidMonster) = 0;
	virtual void handleCollision(Digger& digger) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(Rock& rock) = 0;
	virtual void handleCollision(Diamond& diamond) = 0;
	virtual void handleCollision(Gift& gift) = 0;

private:
	bool m_toDelete = false;
	bool m_gotAGift = false;
};