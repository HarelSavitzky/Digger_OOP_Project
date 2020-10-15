#pragma once
//--------------------include Section --------------------
#include "MovingObjects.h"



class GameManager;
//--------------------Objects Class definition --------------------
class Digger : public MovingObjects
{
public:
	using MovingObjects::MovingObjects;		//	virtual constructor
	
	Digger(sf::Vector2i objectIndex, sf::Vector2f levelSize, sf::Texture& texture,
		char Symbol, sf::RectangleShape limitRec, float pixelSize, sf::Vector2i startingPoint, int numOfRocks, int numOfDiamonds);
		
	void resetMembers(int numOfRocks,int score, int lifes);

	//set properties----------------------
	void increaseScore(int score);
	void increaseRocks();
	void decreaseRocks();
	void decreaseLife();
	void decreaseDiamonds();
	void setLife(int life);

	//get functions----------------------
	int getNumOfRocks() const;
	int getLife() const;
	int getDiamondsToWin() const;
	int getStartingDiamonds() const;
	int getScore() const;

	//virtuals----------------------------
	virtual bool getGotGift();
	virtual bool diggerDead();
	virtual bool toDelete();
	virtual void setDirection(sf::Keyboard::Key key, GameManager& manager, sf::Time deltaTime);

	virtual void handleCollision(Objects& object) override;
	virtual void handleCollision(SmartMonster& smartMonster) override;
	virtual void handleCollision(StupidMonster& stupidMonster) override;
	virtual void handleCollision(Digger& digger) override;
	virtual void handleCollision(Wall& wall) override;
	virtual void handleCollision(Rock& rock) override;
	virtual void handleCollision(Diamond& diamond) override;
	virtual void handleCollision(Gift& gift) override;
private:
	int m_numOfDiamonds;
	int m_numOfRocks;
	int m_firstNumOfDiamonds;
	int m_firstNumOfRocks;
	int m_score;
	int m_lifes;

	bool m_toDelete;
	bool m_isDead;
	bool m_gotAGift;

	Text m_textUpdater;

};