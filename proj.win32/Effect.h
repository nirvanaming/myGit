//
//Effect.h
//
//created by Tim on Aug 25th 2013
//
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "cocos2d.h"
USING_NS_CC;

class Effect :
	public CCNode
{
public:
	Effect(void);
	~Effect(void);

	//explode
	void explode(CCNode *parent, CCPoint pos);
	void killSprite(CCNode *sender);
	void hit(CCNode* parent, CCPoint pos);
	static Effect* create();

};

#endif