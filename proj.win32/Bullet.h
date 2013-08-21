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


class Bullet:public CCSprite
{
private:
	float m_velocityx;
	float m_velocityy;
	CCSize winSize;
	
	void initData(); 
	

public:
	CCSpriteBatchNode* m_bulletSprite;//使用BatchNode构建所有的子弹，减少gl绘画次数 
	CCArray* m_allBulletArray;//保存所有已存在的子弹对象

	Bullet();
	~Bullet();
	virtual bool init();

	virtual void update(float dt);
	
	virtual CCRect bulletRect();
	

	CREATE_FUNC(Bullet);

};

#endif


