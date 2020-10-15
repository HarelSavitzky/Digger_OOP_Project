#pragma once
//--------------------include Section --------------------
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <cstdlib> 
#include <iostream> 
#include <vector>
#include "Const.h"

//--------------------Menu Class definition --------------------
class Menu
{
public:
	Menu();			//constructors
	Menu(float width, float height);

		//handle menu functions--------------
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
		//get function-------------
	int getPressedItem() const { return m_selectedItemIndex; }

private:
	int m_selectedItemIndex;
	sf::Font m_font;
	sf::Text m_menu[MAX_NUMBER_OF_ITEMS];//menu text
	sf::Texture m_texture[MAX_NUMBER_OF_ITEMS];		//menu textres
	sf::RectangleShape m_menuBack[MAX_NUMBER_OF_ITEMS];		//menu picturs in rec
};