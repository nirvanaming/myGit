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
	CCSpriteBatchNode* m_enemySprite;  //ʹ��BatchNode�������ˣ����ٻ滭����
	CCArray* m_allEnemyArray;
public:
	virtual bool init();
	void addEnemy(float dt);           //��ӵ���
    void moveEnemy(float dt);          //�����ƶ� 
	CREATE_FUNC(Enemy);
};

#endif