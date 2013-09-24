//
//Config.h
//
//created by Tim on Aug 27th 2013
//
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <vector>
#include <string>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

extern CCArray *m_allEnemyBulletArray;
extern CCArray *m_allEnemyArray;
extern CCArray *m_allBigBulletArray;

typedef struct Enemies
{
	string showType;
	int showTime;
	int types[3];
	Enemies()
	{
		showType="Repeate";
		showTime=0;
		types[0]=0;
		types[1]=0;
		types[2]=0;
	}
}EnemyInfo;

typedef struct{
	int type;
	string textureName;
	string bulletType;
	int hp;
	int moveType;
	int scoreValue;
}EnemyType;


class Config :
	public CCObject
{
private:
	vector<EnemyInfo> m_enemies;
	vector<EnemyType> m_enemyTypes;

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
	CCUserDefault *highScore;  //the shared highScore(top score)

	static Config* sharedConfig();

	vector<EnemyInfo> getEnemies();
	vector<EnemyType> getEnemyType();
};

#endif