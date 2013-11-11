//
//Effects.h
//
//created by Tim on Oct 31st 2013
//
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Effects :
	public CCNode
{
public:
	Effects(void);
	~Effects(void);

	void explode(CCNode *parent, CCPoint pos);
	void killSprite(CCNode *sender);

	static Effects* create();
	static void sharedExplosion();
};

