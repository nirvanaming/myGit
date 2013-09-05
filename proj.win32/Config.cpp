//
//Config.cpp
//
//created by Tim on Aug 27th 2013
//
#include "Config.h"

using namespace cocos2d;

CCArray *m_allPlayerBulletArray;
CCArray *m_allEnemyBulletArray;
CCArray *m_allEnemyArray;

static  Config *g_config = NULL;

Config::Config(void):
	Score(0)
	,shipHP(3)
{
}


Config::~Config(void)
{
	m_allPlayerBulletArray->release();
	m_allEnemyBulletArray->release();
	m_allEnemyArray->release();
	m_allPlayerBulletArray=NULL;
	m_allEnemyBulletArray=NULL;
	m_allEnemyArray=NULL;
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

Config* Config::sharedConfig()
{

	 if (!g_config) {
        g_config = new Config();
    }
    return g_config;

}