#include "Menu.h"

Menu::Menu()
{}

//---------------Menu constructor--------------------
Menu::Menu(float width, float height)
{
	m_font.loadFromFile("fontn.ttf");

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{													//this function
		m_menu[i].setOutlineThickness(20);			//defines the menu, from text to background
		m_menu[i].setFont(m_font);

			m_menu[i].setCharacterSize(width /15);
			if (i == 0)
			{
				m_menu[i].setFillColor(sf::Color::Green);
				m_menu[i].setString("Play");
				m_menu[i].setPosition(sf::Vector2f((width / 2.35), height / (MAX_NUMBER_OF_ITEMS *2) * 2));
			}
			else
			{
				m_menu[i].setFillColor(sf::Color::White);
				m_menu[i].setString("Quit");
				m_menu[i].setPosition(sf::Vector2f(width / 2.35, height / (MAX_NUMBER_OF_ITEMS *2) * 2.5));
			}
	}
	m_selectedItemIndex = 0;	//the index where we will point ( pley / quit)

	m_texture[0].loadFromFile("menuback.jpg");					
	m_menuBack[0].setSize(sf::Vector2f(width, height));
	m_menuBack[0].setTexture(&m_texture[0]);
	m_menuBack[0].setPosition(0, 0);

	m_texture[1].loadFromFile("menuHeadline.png");
	m_menuBack[1].setSize(sf::Vector2f(width / 2.5, height / 2.5));

	m_menuBack[1].setTexture(&m_texture[1]);
	m_menuBack[1].setPosition(sf::Vector2f((width / 3.2), height / 12));
}
//---------------draw function--------------------
void Menu::draw(sf::RenderWindow& window)
{
	window.draw(m_menuBack[0]);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)		//draw the menu------
	{
		window.draw(m_menu[i]);
	}
	window.draw(m_menuBack[1]);
}
//---------------MoveUp function--------------------
void Menu::MoveUp()
{
	if (m_selectedItemIndex - 1 >= 0)//move up in menu
	{									
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);	
		m_selectedItemIndex--;
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::Green);
	}
}
//---------------MoveDown function--------------------
void Menu::MoveDown()
{
	if (m_selectedItemIndex + 1 < 2)		//move down in menu
	{
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::White);
		m_selectedItemIndex++;
		m_menu[m_selectedItemIndex].setFillColor(sf::Color::Green);
	}
}
