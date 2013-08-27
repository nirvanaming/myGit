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
	CCSpriteBatchNode* m_bulletSprite;//使用BatchNode构建所有的子弹，减少gl绘画次数 
	CCArray* m_allBulletArray;//保存所有已存在的子弹对象

	
	virtual bool init(); //初始化
	//virtual CCRect bulletRect(); //碰撞矩形
	void addNewBullet(float dt);  //添加子弹
	void moveBullet(float dt);   //移动子弹
	

	CREATE_FUNC(Bullet);

};

#endif


