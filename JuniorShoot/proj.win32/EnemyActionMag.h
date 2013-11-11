//
//EnemyActionMag.h
//
//created by tim on Sept 23rd
//

#ifndef _ENEMYACTIONMAG_H_
#define _ENEMYACTIONMAG_H_

#include <string>
#include <vector>
#include "cocos2d.h"
#include "Config.h"
USING_NS_CC;
using namespace std;

class EnemyActionMag
{
private:
	vector<EnemyInfo> m_enemies;
	vector<EnemyType> m_enemyType;
	CCLayer* m_gameLayer;

public:
	EnemyActionMag(CCLayer* gameLayer);
	~EnemyActionMag();

	void loadResource(int dt);
	void addEnemyToGameLayer(int type);
	void repeatAction(CCNode* pSender);
};

#endif