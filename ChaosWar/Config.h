//
//Config.h
//
//created by Tim on Oct 25th 2013
//
#pragma once
#include <vector>
#include <string>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

//extern CCArray *_allEnemyBulletArray;
extern CCArray *_allEnemyArray;
extern CCArray *_allShipBulletArray;



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


class Config: public CCObject
{



public:
	Config(void);
	~Config(void);

	int getScore();
	void setScore(int score);
	void resetConfig(); 
	CCUserDefault *highScore; 

	static Config* sharedConfig();

	vector<EnemyInfo> getEnemies();
	vector<EnemyType> getEnemyType();


private:
	vector<EnemyInfo> _enemies;
	vector<EnemyType> _enemyTypes;
	int _score; 

};

