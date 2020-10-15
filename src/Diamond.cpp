#include "Diamond.h"

//---------------constructor--------------------
Diamond::Diamond()
{}

//---------------toDelete virtual--------------------
bool Diamond::toDelete()
{
		return m_toDelete;	//if the object needs to be deleted
}
//---------------double dispatch functions--------------------
void Diamond::handleCollision(Objects& object)
{
	object.handleCollision(*this);
}
//-----------------------------------
void Diamond::handleCollision(Digger& digger)
{
	digger.increaseScore(DIAMOND_SCORE);		//handle digger collision
	digger.decreaseDiamonds();
	m_toDelete = true;
}
//-----------------------------------
void Diamond::handleCollision(SmartMonster& smartMonster){}
void Diamond::handleCollision(StupidMonster& stupidMonster){}
void Diamond::handleCollision(Wall& wall){}
void Diamond::handleCollision(Rock& rock){}
void Diamond::handleCollision(Diamond& diamond){}
void Diamond::handleCollision(Gift& gift){}