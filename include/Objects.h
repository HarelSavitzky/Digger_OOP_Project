#pragma once
//--------------------include Section --------------------
#include <Text.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "Const.h"
#include <iostream>

//--------------------forward decleration Section --------------------
class MovingObjects;
class StaticObjects;
class Monster;
class StupidMonster;
class SmartMonster;
class Digger;
class Wall;
class Rock;
class Diamond;
class Gift;

//--------------------Objects Class definition --------------------
class Objects
{
public:
	//constructor ---------------
	Objects();
	Objects(sf::Vector2i objectIndex, sf::Vector2f levelSize, sf::Texture& texture,
		char Symbol, sf::RectangleShape limitRec, float pixelSize);

	//get functions--------------------------------------
	sf::Vector2f getLocation() const;
	char getSymbol() const;
	sf::Vector2i getObjectIndex() const;
	sf::RectangleShape getLimitsRectangle() const;
	sf::Sprite& getSprite();

	//--------------------Virtuals --------------------
	virtual void draw(sf::RenderWindow& window);

	virtual void handleCollision(Objects& object) = 0;
	virtual void handleCollision(SmartMonster& smartMonster) = 0;
	virtual void handleCollision(StupidMonster& stupidMonster) = 0;
	virtual void handleCollision(Digger& digger) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(Rock& rock) = 0;
	virtual void handleCollision(Diamond& diamond) = 0;
	virtual void handleCollision(Gift& gift) = 0;

private:
	sf::RectangleShape m_objectRec;
	sf::RectangleShape m_limitsRec;
	sf::Vector2f m_location;
	sf::Vector2i m_index;
	sf::Sprite m_objectSprite;
	int m_textSymbol;
};