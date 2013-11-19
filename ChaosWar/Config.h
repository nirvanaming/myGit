//
//Config.h
//
//created by Tim on Oct 25th 2013
//
#pragma once
#include <vector>
//#include <string>
#include "cocos2d.h"
using namespace std;
USING_NS_CC;

//extern CCArray *_allEnemyBulletArray;
extern CCArray *_allEnemyArray;
extern CCArray *_allShipBulletArray;


struct EnemyInfo
{
	//string showType;
	int showTime;
    int types[3];
	
};


struct EnemyType{
public:

	int type;
	char* textureName;
	char* bulletType;
	int hp;
	int moveType;
	int scoreValue;

};



class Config: public CCObject
{


public:
	
	~Config();

	int getScore();
	void setScore(int score);
	void resetConfig(); 
	CCUserDefault *highScore; 

	static Config* sharedConfig();

	vector<EnemyInfo> getEnemies();
	vector<EnemyType> getEnemyType();

private:
	Config();
	static Config* g_config;
	vector<EnemyInfo> _enemies;
	vector<EnemyType> _enemyTypes;
	int _score; 

	//////////////////////
	class CCGarbo
	{
	public:
		~CCGarbo()
		{
			if(g_config)
				delete g_config;
		}

	};
	static CCGarbo Garbo;
};

