//
//RDpad.h
//
//created by Tim on Oct 27th 2013
//

#pragma once
#include "cocos2d.h"
USING_NS_CC;
class RightDPad;

class RDpadDelegate
{
public:

	virtual void didChangeRotationTo(RightDPad* RDpad,float degree,CCPoint direction)=0;
	virtual void isHoldingRotation(RightDPad* RDpad,float degree,CCPoint direction)=0;
	virtual void RightDPadTouchEnded(RightDPad* RDpad)=0;

	/*virtual void RightDPadChangeDirectionTo(RightDPad* RDpad,CCPoint direction)=0;*/
};

class RightDPad :
	public CCSprite,public CCTargetedTouchDelegate
{
public:
	RightDPad(void);
	~RightDPad(void);

	static RightDPad* create(CCString* fileName, float radius);
	bool initWithFile(CCString* fileName, float radius);

	void onEnterTransitionDidFinish();
	void onExit();
	void update(float dt);

	virtual bool ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent);

	void updateRDirectionForTouchLocation(CCPoint location);
	CC_SYNTHESIZE(RDpadDelegate*,_rdelegate,RDelegate);
	CC_SYNTHESIZE(bool,_isHelding,ISHelding);

protected:
	float _radius;
	CCPoint _direction;
	float _degree;
	CCPoint _to_direction;

};

