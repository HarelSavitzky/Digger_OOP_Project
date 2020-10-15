#pragma once
//--------------------include Section --------------------
#include "Monster.h"

class GameManager;
//--------------------StupidMonster Class definition --------------------
class StupidMonster : public Monster
{
public:
	using Monster::Monster;
	StupidMonster();


	//--------------------Virtuals --------------------
	virtual bool diggerDead();
	virtual void setDirection(GameManager& manager, sf::Time deltaTime) override;

	virtual void handleCollision(Objects& object) override;
	virtual void handleCollision(SmartMonster& smartMonster) override;
	virtual void handleCollision(StupidMonster& stupidMonster) override;
	virtual void handleCollision(Digger& digger) override;
	virtual void handleCollision(Wall& wall) override;
	virtual void handleCollision(Rock& rock) override;
	virtual void handleCollision(Diamond& diamond) override;
	virtual void handleCollision(Gift& gift) override;
private:
	bool m_isDead;

};