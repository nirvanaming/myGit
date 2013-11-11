//
//Unit.h
//
//created by Tim on Oct 21st 2013
//
#pragma once
#include "cocos2d.h"
#include "Defines.h"
USING_NS_CC;

class Unit :
	public CCSprite
{
public:
	Unit(void);
	~Unit(void);


	virtual bool isActive()=0;
	virtual void hurt(float damage)=0;
	virtual void destroy()=0;
	virtual CCRect Rect()=0;
	virtual int getDamage()=0;

	void update(float dt)=0;


	//measurement
	CC_SYNTHESIZE(float,_centerToSides,CenterToSides);
	CC_SYNTHESIZE(float,_centerToBottom,CenterToBottom);
};

