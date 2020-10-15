#include "Rock.h"
#include "Board.h"

Rock::Rock()
{}

//---------------virtual functions--------------------
bool Rock::toDelete()
{
	return m_toDelete;
}
//---------------double dispatch functions--------------------
void Rock::handleCollision(Objects& object)
{
	object.handleCollision(*this);
}
//-----------------------------------
void Rock::handleCollision(SmartMonster& smartMonster)
{
	smartMonster.stopObject();	
}
//-----------------------------------
void Rock::handleCollision(StupidMonster& stupidMonster)	//rock blocks monsters
{
	stupidMonster.stopObject();
}
//-----------------------------------
void Rock::handleCollision(Digger& digger)		//eaten by digger
{
	digger.decreaseRocks();
	m_toDelete = true;
}
//-----------------------------------
void Rock::handleCollision(Wall& wall){}
void Rock::handleCollision(Rock& rock){}
void Rock::handleCollision(Diamond& diamond){}
void Rock::handleCollision(Gift& gift){}