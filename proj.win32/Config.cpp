#include "Config.h"

using namespace cocos2d;

static  Config *g_config = NULL;

Config::Config(void):
	Score(0)
	,shipHP(3)
{
}


Config::~Config(void)
{
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