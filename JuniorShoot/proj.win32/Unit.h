//
//Unit.h
//
//created by Tim on Sept 13rd
//
#ifndef _UNIT_
#define _UNIT_

#include "cocos2d.h"
USING_NS_CC;

class Unit :
	public CCSprite
{
public:
	Unit(void);
	~Unit(void);

public:
	virtual void destroy()=0;
	virtual void hurt()=0;
	virtual CCRect Rect()=0;
	virtual bool isActive()=0;
};

#endif