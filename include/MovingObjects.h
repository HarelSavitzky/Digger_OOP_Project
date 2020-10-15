#pragma once
//--------------------include Section --------------------

#include "Objects.h"
class GameManager;
//--------------------Objects Class definition --------------------
class MovingObjects : public Objects
{
public:
	using Objects::Objects;
	MovingObjects(sf::Vector2i objectIndex, sf::Vector2f levelSize, sf::Texture& texture,
		char Symbol, sf::RectangleShape limitRec, float pixelSize, sf::Vector2i startingPoint);

	//handle movement funcions--------------
	void setDeltaTime(sf::Time deltaTime);
	void move(sf::Vector2f direction, sf::Time deltaTime);
	void stopObject();

	//-------if in game bounds---
	bool inGameBounds(sf::Keyboard::Key key);

	//get functions-----------
	sf::Vector2f getDirection() const;
	sf::Vector2i getStartingPoint() const;
	sf::Time getDeltaTime() const;
	sf::Keyboard::Key getKey() const;


	//--------------------Virtuals --------------------
	virtual void setDirection(sf::Keyboard::Key key);

	virtual void handleCollision(Objects& object) = 0;
	virtual void handleCollision(SmartMonster& smartMonster) = 0;
	virtual void handleCollision(StupidMonster& stupidMonster) = 0;
	virtual void handleCollision(Digger& digger) = 0;
	virtual void handleCollision(Wall& wall) = 0;
	virtual void handleCollision(Rock& rock) = 0;
	virtual void handleCollision(Diamond& diamond) = 0;
	virtual void handleCollision(Gift& gift) = 0;
private:
	sf::Vector2f m_direction;
	sf::Time m_deltaTime;
	sf::Keyboard::Key m_key;
	sf::Vector2i m_startingPoint;
};