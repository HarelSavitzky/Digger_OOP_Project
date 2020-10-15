#pragma once

//--------------------include Section --------------------
#include "StaticObjects.h"

//--------------------Gift Class definition --------------------
class Gift : public StaticObjects
{
public:
	using StaticObjects::StaticObjects;
	Gift();	//constructor ---------------


	//--------------------Virtuals --------------------

	virtual bool getGotGift();
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
	bool m_gotAGift = false;
};