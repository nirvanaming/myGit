//
//Enemy.h
//
//created by Tim on Aug 21st 2013
//

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "cocos2d.h"
USING_NS_CC;

class Enemy :
	public CCLayer
{
public:
	Enemy(void);
	~Enemy(void);
public:
	CCSpriteBatchNode* m_enemySprite;  //使用BatchNode构建敌人，减少绘画次数
	CCArray* m_allEnemyArray;
public:
	virtual bool init();
	void addEnemy(float dt);           //添加敌人
    void moveEnemy(float dt);          //敌人移动 
	CREATE_FUNC(Enemy);
};

#endif