#include "Wall.h"

Wall::Wall()
{}

//---------------double dispatch functions--------------------
void Wall::handleCollision(Objects& object)
{
	object.handleCollision(*this);
}
//---------------
void Wall::handleCollision(Digger& digger)
{
	digger.stopObject();
}
//---------------
void Wall::handleCollision(SmartMonster& smartMonster)	//stops everyone
{
	smartMonster.stopObject();
}
//---------------
void Wall::handleCollision(StupidMonster& stupidMonster)
{
	stupidMonster.stopObject();
}
//---------------
void Wall::handleCollision(Wall& wall){}
void Wall::handleCollision(Rock& rock){}
void Wall::handleCollision(Diamond& diamond){}
void Wall::handleCollision(Gift& gift){}
