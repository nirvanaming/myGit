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
	CCSpriteBatchNode* m_bulletSprite;//ʹ��BatchNode�������е��ӵ�������gl�滭���� 
	CCArray* m_allBulletArray;//���������Ѵ��ڵ��ӵ�����

	Bullet();
	~Bullet();
	virtual bool init();

	virtual void update(float dt);
	
	virtual CCRect bulletRect();
	

	CREATE_FUNC(Bullet);

};

#endif


