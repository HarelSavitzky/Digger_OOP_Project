#pragma once

//--------------------include Section --------------------
#include "StaticObjects.h"
#include "SmartMonster.h"
#include "StupidMonster.h"
//--------------------Wall Class definition --------------------
class Wall : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
	//constructor ---------------
	Wall();

	//--------------------Virtuals --------------------
	virtual void handleCollision(Objects& object) override;
	virtual void handleCollision(SmartMonster& smartMonster) override;
	virtual void handleCollision(StupidMonster& stupidMonster) override;
	virtual void handleCollision(Digger& digger) override;
	virtual void handleCollision(Wall& wall) override;
	virtual void handleCollision(Rock& rock) override;
	virtual void handleCollision(Diamond& diamond) override;
	virtual void handleCollision(Gift& gift) override;
private:
};