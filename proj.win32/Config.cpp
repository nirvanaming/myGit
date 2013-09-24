//
//Config.cpp
//
//created by Tim on Aug 27th 2013
//
#include "Config.h"
using namespace std;

using namespace cocos2d;

CCArray *m_allEnemyArray;
CCArray *m_allBigBulletArray;
CCArray *m_allEnemyBulletArray;

static  Config *g_config = NULL;

Config::Config(void):Score(0),shipHP(3)
{
	EnemyInfo temp;
	temp.showType="Repeate";
	temp.showTime=2;
	temp.types[1]=1;
	temp.types[2]=2;
	m_enemies.push_back(temp);

	temp.showTime=5;
	temp.types[0]=3;
	temp.types[1]=4;
	temp.types[2]=5;
	m_enemies.push_back(temp);

	EnemyType enemyType;
	enemyType.type=0;
	enemyType.textureName="E0.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=1;
	enemyType.moveType=0;
	enemyType.scoreValue=20;
	m_enemyTypes.push_back(enemyType);

	enemyType.type=1;
	enemyType.textureName="E1.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=2;
	enemyType.moveType=1;
	enemyType.scoreValue=40;
	m_enemyTypes.push_back(enemyType);

	enemyType.type=2;
	enemyType.textureName="E2.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=4;
	enemyType.moveType=2;
	enemyType.scoreValue=60;
	m_enemyTypes.push_back(enemyType);

	enemyType.type=3;
	enemyType.textureName="E3.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=6;
	enemyType.moveType=3;
	enemyType.scoreValue=80;
	m_enemyTypes.push_back(enemyType);

	enemyType.type=4;
	enemyType.textureName="E4.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=8;
	enemyType.moveType=2;
	enemyType.scoreValue=120;
	m_enemyTypes.push_back(enemyType);

	enemyType.type=5;
	enemyType.textureName="E5.png";
	enemyType.bulletType="W2.png";
	enemyType.hp=10;
	enemyType.moveType=2;
	enemyType.scoreValue=180;
	m_enemyTypes.push_back(enemyType);
	
}


Config::~Config(void)
{
	m_allBigBulletArray->release();
	m_allBigBulletArray=NULL;
	m_allEnemyArray->release();
	m_allEnemyArray=NULL;
	m_allEnemyBulletArray->release();
	m_allEnemyBulletArray=NULL;
}


int Config::getScore()
{
	return Score;
}

void Config::setScore(int score)
{
	Score+=score;
}

int Config::getShipHP()
{

	return shipHP;
}

void Config::setShipHP()
{

	shipHP--;
}

void Config::resetConfig()
{

	Score=0;
	shipHP=3;

}

CCUserDefault *highScore=CCUserDefault::sharedUserDefault(); 

Config* Config::sharedConfig()
{

	 if (!g_config) {
        g_config = new Config();
    }
    return g_config;

}

vector<EnemyInfo> Config::getEnemies()
{
	return m_enemies;
}

vector<EnemyType> Config::getEnemyType()
{
	return m_enemyTypes;
}