//
//EnemyManage.h
//
//created by Tim on Oct 28th 2013
//
#pragma once
#include <vector>
#include "cocos2d.h"
#include "Config.h"
#include "Enemys.h"
USING_NS_CC;

class EnemyManage
{

private:
	vector<EnemyInfo> _enemies;
	vector<EnemyType> _enemyType;
	CCLayer* _gameLayer;
	Enemys* enemy;


public:
	EnemyManage(CCLayer* gameLayer);
	~EnemyManage();

	void loadResource(int dt);
	void addEnemyToGameLayer(int type);
	void repeatAction(CCNode* pSender);
	void followHero(CCNode* pSender);
	void update(float dt);

	
};

