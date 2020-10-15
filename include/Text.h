#pragma once

//--------------------include Section --------------------
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <cstdlib> 
#include <iostream> 
#include "Const.h"
#include <string>
#include <string.h>
#include <cmath>

//--------------------Text Class definition --------------------
class Text
{
public:
	//build----------
	void buildInfoBars();
	void buildMessages();
	//draw------------
	void draw(sf::RenderWindow& window);
	void drawGiftMessage(sf::RenderWindow& window, int message);
	//set---------------
	void initializeStats(int score, int time, int rocks, int lifes, int level);
	void setSpecificStat(int stat, int num);
	void setTime(int time);

	~Text() = default;
private:
	sf::Font m_font;

	sf::Text m_infoBarText[INFO_ITEMS];
	sf::Text m_stats[INFO_ITEMS];

	sf::Text m_giftMessages[GIFT_MESSAGE];
};


