//
//Enemy.h
//
//created by Tim on Aug 21st 2013
//

#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Unit.h"
#include <string>
#include "cocos2d.h"
#include "Config.h"
USING_NS_CC;

class Enemy :
	public Unit
{
public:
	Enemy(void);
	~Enemy(void);
private:
	bool m_active;
	int m_speed;
	int m_bulletSpeed;
	int m_HP;
	int m_moveType;
	int m_scoreValue;
	float m_delayTime;

public:
	
	static Enemy* create(EnemyType type);

	virtual bool initWithFile(EnemyType type);
	virtual void update(float dt);
	//virtual void move();
	virtual void hurt();
	virtual void destroy();
	virtual CCRect Rect();
	virtual bool isActive();          
	virtual void shoot(float dt);
	//void spriteMoveFinished(CCNode* sender);
	static void sharedEnemy();
	int getMoveType();


};

#endif