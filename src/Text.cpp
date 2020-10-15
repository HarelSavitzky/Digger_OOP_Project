#include "Text.h"

//---------------------buildInfoBars function --------------------------
void Text::buildInfoBars()
{
	m_font.loadFromFile("fontn.TTF");
	int space = 150;
	for (int i = 0; i < INFO_ITEMS; i++)			//function to define the bars of stats----
	{
		m_infoBarText[i].setFont(m_font);
		m_infoBarText[i].setPosition(sf::Vector2f((100 * i) + (space * i), 20));
		m_infoBarText[i].setColor(sf::Color::Green);
		m_infoBarText[i].setCharacterSize(40);
		m_infoBarText[i].setOutlineThickness(10);
		if (i == LEVEL)
			m_infoBarText[i].setString("LEVEL:");
		if (i == LIFE)
		{
			m_infoBarText[i].setString("LIFE:");
			m_infoBarText[i].setPosition(sf::Vector2f((100 * i) + (space * i) + 30, 20));
		}
		if (i == ROCKS)
			m_infoBarText[i].setString("Rocks:");
		if (i == TIME)
		{
			m_infoBarText[i].setString("TIME:");
			m_infoBarText[i].setPosition(sf::Vector2f((100 * i) + (space * i) + 30, 20));
		}
		if (i == SCORE)
		{
			m_infoBarText[i].setString("SCORE:");
			m_infoBarText[i].setPosition(sf::Vector2f((100 * i) + (space * i) + 50, 20));
		}
	}
	buildMessages();
}

//---------------------initializeStats function --------------------------
void Text::initializeStats(int score, int time, int rocks, int lifes, int level)
{
	int space = 200;
	sf::Text tempText;						//function to build and initialize the stats values
	tempText.setFont(m_font);
	tempText.setFillColor(sf::Color::White);
	tempText.setCharacterSize(35);
	tempText.setOutlineThickness(6); 

	for (int i = 0; i < INFO_ITEMS; i++)
	{
		tempText.setPosition(sf::Vector2f((100 * i) + (space * i) , 25));
		m_stats[i] = tempText;
		if (i == LEVEL)
		{
			m_stats[LEVEL].setString(std::to_string(level));
			m_stats[LEVEL].setPosition(sf::Vector2f((100 * i) + (space * i) + 180, 25));
		}
		if (i == LIFE)
		{
			m_stats[LIFE].setString(std::to_string(lifes));
			m_stats[LIFE].setPosition(sf::Vector2f((100 * i) + (space * i) + 110, 25));
		}
		if (i == ROCKS)
		{
			m_stats[ROCKS].setString(std::to_string(rocks));
			m_stats[ROCKS].setPosition(sf::Vector2f((100 * i) + (space * i) + 80, 25));
		}
		if (i == TIME)
		{
			m_stats[TIME].setString(std::to_string(time));
			m_stats[TIME].setPosition(sf::Vector2f((100 * i) + (space * i) + 40, 25));
		}
		if (i == SCORE)
		{
			m_stats[SCORE].setString(std::to_string(score));
			m_stats[SCORE].setPosition(sf::Vector2f((100 * i) + (space * i) + 50, 25));
		}

	}
}
//---------------------buildMessages function ---------------------
void Text::buildMessages()
{
	for (int i = 0; i < GIFT_MESSAGE; i++)			//function to build the gift messages
	{
		m_giftMessages[i].setFont(m_font);
		m_giftMessages[i].setPosition(sf::Vector2f(WINDOW_WIDTH / 3, 100 * (i + 1)));
		m_giftMessages[i].setColor(sf::Color::Yellow);
		m_giftMessages[i].setCharacterSize(70);
		m_giftMessages[i].setOutlineThickness(2);

		if (i == SCORE_MESSAGE)
			m_giftMessages[i].setString("Score +50");
		if (i == ROCK_MESSAGE)
			m_giftMessages[i].setString("Rock +1");
		if (i == TIME_MESSAGE)
			m_giftMessages[i].setString("Time +30");
	}
}
//---------------------setTime function ---------------------
void Text::setTime(int time)		//function to set the time 
{										//seperated because he changes colors
	if (time == -1)
	{
		m_stats[TIME].setString("X");
		m_stats[TIME].setColor(sf::Color::White);
	}
	else
	{
		m_stats[TIME].setString(std::to_string(time));
		if (time <= 10)
			m_stats[TIME].setColor(sf::Color::Red);
		else
			m_stats[TIME].setColor(sf::Color::White);
	}
}
//---------------------setSpecificStat function ---------------------
void Text::setSpecificStat(int stat, int num)
{
	m_stats[stat].setString(std::to_string(num));	//set stat
}
//---------------------drawGiftMessage function ---------------------
void Text::drawGiftMessage(sf::RenderWindow& window, int message)
{
	window.draw(m_giftMessages[message]);		//draw a gift message
}
//---------------------draw function --------------------------
void Text::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < INFO_ITEMS; i++)			//give const-----------------------
	{
		window.draw(m_infoBarText[i]);
		window.draw(m_stats[i]);
	}
}
