//
//bullet.h
//
//Created by Tim on Aug 14th, 2013
//update on Aug 16th, 2013
//


#ifndef _BULLET_
#define _BULLET_

#include "cocos2d.h"
USING_NS_CC;


class Bullet:public CCLayer
{
public:
	Bullet();
	~Bullet();

public:
	CCSpriteBatchNode* m_bulletSprite;//using BatchNode to create bullet£¬reduce the GL create times 
	//CCArray* m_allBulletArray;//save all the bullets array
	CCSpriteBatchNode* m_enemyBulletSprite;

	
	virtual bool init(); //init
	//virtual CCRect bulletRect(); //collide rect
	void addNewShipBullet(float dt);  //add bullets
	void addNewEnemyBullet(float dt);
	void moveShipBullet(float dt);   //move bullets
	void moveEnemyBullet(float dt);
	

	CREATE_FUNC(Bullet);

};

#endif


