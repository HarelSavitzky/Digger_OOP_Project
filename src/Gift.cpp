#include "Gift.h"

Gift::Gift()
{}
//---------------virtual functions--------------------
bool Gift::toDelete()
{
	return m_toDelete;
}
//------------------------------------
bool Gift::getGotGift()
{
	return m_gotAGift;
}
//---------------double dispatch functions--------------------
void Gift::handleCollision(Objects& object)
{
	object.handleCollision(*this);
}
//------------------------------------
void Gift::handleCollision(Digger& digger)
{
	m_gotAGift = true;				//got gift handle
	m_toDelete = true;
}
//------------------------------------
void Gift::handleCollision(Wall& wall){}
void Gift::handleCollision(Rock& rock){}
void Gift::handleCollision(Diamond& diamond){}
void Gift::handleCollision(Gift& gift){}
void Gift::handleCollision(SmartMonster& smartMonster) {}
void Gift::handleCollision(StupidMonster& stupidMonster) {}