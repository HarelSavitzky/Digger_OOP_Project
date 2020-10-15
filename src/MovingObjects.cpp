//include section------------------
#include "MovingObjects.h"
#include "GameManager.h"

//------------------------------------MovingObjects constructor------------------------------------
MovingObjects::MovingObjects(sf::Vector2i objectIndex, sf::Vector2f levelSize, sf::Texture& texture,
	char Symbol, sf::RectangleShape limitRec, float pixelSize, sf::Vector2i startingPoint) :
	Objects(objectIndex, levelSize, texture, Symbol, limitRec, pixelSize)
{
	m_startingPoint = startingPoint;	//save the starting points of moving
}
//------------------------------------Moving Handle functions------------------------------------
//-----------------------setDirection functions----------------------
void MovingObjects::setDirection(sf::Keyboard::Key key)
{
	m_key = key;							//will set speed comparing to object&level size
	int movingRate = this->getSprite().getGlobalBounds().width * 2.1;
	if (this->getSymbol() == DIGGER)
		movingRate = this->getSprite().getGlobalBounds().width * 3;


	switch (key)				//guided by a key->(also monster)each key means like he does....
	{												//direction!
	case sf::Keyboard::Key::Up:
		m_direction = sf::Vector2f(0, -movingRate); break;
	case sf::Keyboard::Key::Down:
		m_direction = sf::Vector2f(0, movingRate); break;
	case sf::Keyboard::Key::Right:
		m_direction = sf::Vector2f(movingRate, 0); break;
	case sf::Keyboard::Key::Left:
		m_direction = sf::Vector2f(-movingRate, 0); break;
	case sf::Keyboard::Key::Space:
		m_direction = sf::Vector2f(0, 0); break;
	}
}
//-----------------------move functions----------------------
void MovingObjects::move(sf::Vector2f direction, sf::Time deltaTime)
{
	getSprite().move(direction * deltaTime.asSeconds());
	setDeltaTime(deltaTime);
}
//-----------------------stopObject functions----------------------
void MovingObjects::stopObject()
{
	this->move(-m_direction, getDeltaTime());
}
//-----------------------setDeltaTime functions----------------------
void MovingObjects::setDeltaTime(sf::Time deltaTime)
{
	m_deltaTime = deltaTime;
}
//-----------------------inGameBounds functions----------------------
bool MovingObjects::inGameBounds(sf::Keyboard::Key key)
{
	switch (key)					//function to check if a object is in the game bounds
	{
	case sf::Keyboard::Key::Up:			//also guided by keys
		if (getLimitsRectangle().getPosition().y -
			(getLimitsRectangle().getGlobalBounds().height / 2)
			>= getSprite().getPosition().y)
			return false;
		break;
	case sf::Keyboard::Key::Down:
		if (getLimitsRectangle().getPosition().y +
			(getLimitsRectangle().getGlobalBounds().height / 2) <=
			getSprite().getPosition().y + getSprite().getGlobalBounds().height)
			return false;
		break;
	case sf::Keyboard::Key::Left:
		if (getLimitsRectangle().getPosition().x -
			(getLimitsRectangle().getGlobalBounds().width / 2) >=
			getSprite().getPosition().x)
			return false;
		break;
	case sf::Keyboard::Key::Right:
		if (getLimitsRectangle().getPosition().x +
			(getLimitsRectangle().getGlobalBounds().width / 2) <=
			getSprite().getPosition().x + getSprite().getGlobalBounds().height)
			return false;
		break;
	case KEYBOARD_SPACE:
		return false;
		break;
	}
	return true;
}
//------------------------------------get functions------------------------------------
//-----------------------getDeltaTime functions----------------------
sf::Time MovingObjects::getDeltaTime() const
{
	return m_deltaTime;
}
//-----------------------getDirection functions----------------------
sf::Vector2f MovingObjects::getDirection() const
{
	return m_direction;
}
//-----------------------getStartingPoint functions----------------------
sf::Vector2i MovingObjects::getStartingPoint() const
{
	return m_startingPoint;
}
//-----------------------getKey functions----------------------
sf::Keyboard::Key MovingObjects::getKey() const
{
	return m_key;
}
