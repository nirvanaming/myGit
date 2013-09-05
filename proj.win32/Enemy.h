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
	CCSpriteBatchNode* m_enemySprite;  //using BatchNode to create enemies£¬reduce the GL create times
	//CCArray* m_allEnemyArray;
public:
	virtual bool init();
	void addEnemy(float dt);           //add enemy
   // void moveEnemy();    //enemy move, there are 2 ways to move enemies
	void spriteMoveFinished(CCNode* sender);
	//void moveLogic(float dt);
	CREATE_FUNC(Enemy);

};

#endif