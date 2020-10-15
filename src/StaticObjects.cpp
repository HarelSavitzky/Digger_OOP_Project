#include "StaticObjects.h"

StaticObjects::StaticObjects(){}
//---------------------virtuals function --------------------------
bool StaticObjects::toDelete()
{
	return m_toDelete;
}
//--------------------
bool StaticObjects::getGotGift()
{
	return m_gotAGift;
}
//--------------------
void StaticObjects::draw(sf::RenderWindow& window)
{
	window.draw(getSprite());
}
