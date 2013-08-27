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
	static Effect* create();

};

#endif