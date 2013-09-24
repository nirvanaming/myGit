//
//BigBullet.h
//
//created by Tim on Sep 13rd
//
#ifndef _BIGBULLET_
#define _BIGBULLET_

#include "Unit.h"
#include "cocos2d.h"

USING_NS_CC;

class BigBullet :
	public Unit
{
public:
	BigBullet(void);
	~BigBullet(void);

private:
	int moveSpeed;
	int m_HP;

public:
	bool m_active;
	static BigBullet* create(const char* weapon,int speed);
	virtual bool initWithFile(const char* weapon,int speed);
	virtual void update(float dt);
	virtual void hurt();
	virtual void destroy();
	virtual CCRect Rect();
	virtual bool isActive();

	//CREATE_FUNC(BigBullet);


};

#endif