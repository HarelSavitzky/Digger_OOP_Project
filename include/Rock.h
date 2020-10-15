#pragma once

//--------------------include Section --------------------
#include "StaticObjects.h"
class Board;
//--------------------Rock Class definition --------------------
class Rock : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
	Rock();

	//--------------------Virtuals --------------------
	virtual bool toDelete();

	virtual void handleCollision(Objects& object) override;
	virtual void handleCollision(SmartMonster& smartMonster) override;
	virtual void handleCollision(StupidMonster& stupidMonster) override;
	virtual void handleCollision(Digger& digger) override;
	virtual void handleCollision(Wall& wall) override;
	virtual void handleCollision(Rock& rock) override;
	virtual void handleCollision(Diamond& diamond) override;
	virtual void handleCollision(Gift& gift) override;
private:
	bool m_toDelete = false;
};