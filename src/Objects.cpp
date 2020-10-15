#include "Objects.h"

#include "Board.h"

Objects::Objects()
{}
//------------------------------------Objects constructor------------------------------------
Objects::Objects(sf::Vector2i objectIndex, sf::Vector2f levelSize, sf::Texture &texture,
	char Symbol, sf::RectangleShape limitRec, float pixelSize)
{
	m_limitsRec = limitRec;
	m_index = objectIndex;

	m_location.x = ((WINDOW_WIDTH / 2) - ((levelSize.x * pixelSize) / 2)) + (objectIndex.y * pixelSize);
	m_location.y = ((WINDOW_HEIGHT / 2) - ((levelSize.y * pixelSize) / 2)) + (objectIndex.x * pixelSize);
	texture.setSmooth(true);
	m_objectSprite.setTexture(texture);
	

	auto size = m_objectSprite.getTexture()->getSize();
	m_objectSprite.setPosition(sf::Vector2f(m_location.x, m_location.y));		//set different size for digger and monsters-----
	if(Symbol == DIGGER)																//so they wont stuck everywhere
		m_objectSprite.setScale((pixelSize * 0.65) / m_objectSprite.getGlobalBounds().width,
		(pixelSize * 0.5) / m_objectSprite.getGlobalBounds().height);
	else if (Symbol == MONSTER)
		m_objectSprite.setScale((pixelSize * 0.7) / m_objectSprite.getGlobalBounds().width,
		(pixelSize * 0.7) / m_objectSprite.getGlobalBounds().height);
	else
	m_objectSprite.setScale(pixelSize / m_objectSprite.getGlobalBounds().width ,
		pixelSize	 / m_objectSprite.getGlobalBounds().height );
	
	m_textSymbol = Symbol;
}
//-------------getObjectIndex function--------------------
sf::Vector2i Objects::getObjectIndex() const
{
	return m_index;
}
//-------------getLimitsRectangle function--------------------
sf::RectangleShape Objects::getLimitsRectangle() const
{
	return m_limitsRec;
}
//-------------getLocation function--------------------
sf::Vector2f Objects::getLocation() const
{
	return m_location;
}
//-------------getSymbol function--------------------
char Objects::getSymbol() const
{
	return m_textSymbol;
}
//-------------getSprite function--------------------
sf::Sprite& Objects::getSprite()
{
	return m_objectSprite;
}
//------------------------------------draw function------------------------------------
void Objects::draw(sf::RenderWindow& window)
{
	window.draw(m_objectSprite);
}

