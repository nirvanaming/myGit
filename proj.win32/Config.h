//
//Config.h
//
//created by Tim on Aug 27th 2013
//
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "cocos2d.h"
USING_NS_CC;

extern CCArray *m_allPlayerBulletArray;
extern CCArray *m_allEnemyBulletArray;
extern CCArray *m_allEnemyArray;

class Config :
	public CCObject
{
public:
	Config(void);
	~Config(void);

	int getScore();
	void setScore(int score);
	int getShipHP();
	void setShipHP();
	int Score;     //game score
	int shipHP;    //ship HP
	void resetConfig(); //reset shipHP and score

	static Config* sharedConfig();
};

#endif