//
//Config.cpp
//
//created by Tim on Oct 25th 2013
//
#include "Config.h"
USING_NS_CC;

CCArray *_allEnemyArray;
CCArray *_allShipBulletArray;
//CCArray *_allEnemyBulletArray;



Config* Config::g_config=NULL;

Config::Config()
{
	_score=0;

	EnemyInfo temp;
	//temp.showType="Repeate";
	temp.showTime=1;;
	temp.types[0]=0;
	temp.types[1]=1;
	temp.types[2]=2;
	_enemies.push_back(temp);

	temp.showTime=5;
	temp.types[0]=3;
	temp.types[1]=4;
	temp.types[2]=5;
	_enemies.push_back(temp);

	EnemyType enemyType;
	enemyType.type=0;
	enemyType.textureName="E0.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=1;
	enemyType.moveType=0;
	enemyType.scoreValue=20;
	_enemyTypes.push_back(enemyType);

	enemyType.type=1;
	enemyType.textureName="E1.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=1;
	enemyType.moveType=1;
	enemyType.scoreValue=40;
	_enemyTypes.push_back(enemyType);

	enemyType.type=2;
	enemyType.textureName="E2.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=1;
	enemyType.moveType=2;
	enemyType.scoreValue=60;
	_enemyTypes.push_back(enemyType);

	enemyType.type=3;
	enemyType.textureName="E3.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=1;
	enemyType.moveType=3;
	enemyType.scoreValue=80;
	_enemyTypes.push_back(enemyType);

	enemyType.type=4;
	enemyType.textureName="E4.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=1;
	enemyType.moveType=2;
	enemyType.scoreValue=120;
	_enemyTypes.push_back(enemyType);

	enemyType.type=5;
	enemyType.textureName="E5.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=1;
	enemyType.moveType=2;
	enemyType.scoreValue=180;
	_enemyTypes.push_back(enemyType);
}




Config::~Config()
{
	_allEnemyArray->release();
	_allEnemyArray=NULL;

	_allShipBulletArray->release();
	_allShipBulletArray=NULL;
	
}


//bool Config::init()
//{
//	bool bRet=false;
//	do
//	{
//	
//	_score=0;
//
//	
//
//	bRet=true;
//	}while(0);
//	return bRet;
//}

int Config::getScore()
{
	return _score;
}

void Config::setScore(int score)
{
	_score+=score;
}


void Config::resetConfig()
{
	_score=0;
}


CCUserDefault *highScore=CCUserDefault::sharedUserDefault();

Config* Config::sharedConfig()
{

	if(!g_config)
	{
		//g_config=Config::create();
		g_config=new Config();
	}
	return g_config;
}


vector<EnemyInfo> Config::getEnemies()
{
	return _enemies;
}

vector<EnemyType> Config::getEnemyType()
{
	return _enemyTypes;
}


