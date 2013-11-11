//
//DPad.h
//
//created by Tim on Oct 21st 2013
//
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class DPad;

class DPadDelegate
{
public:
	virtual void didChangeDirectionTo(DPad* simpleDPad,CCPoint direction,float acce)=0;
	virtual void isHoldingDirection(DPad* simpleDpad,CCPoint direction,float acce)=0;
	virtual void simpleDPadTouchEnded(DPad* simpleDpad)=0;
};



class DPad :
	public CCSprite, public CCTargetedTouchDelegate
{
public:
	DPad(void);
	~DPad(void);

	static DPad* create(CCString* fileName, float radius);
	bool initWithFile(CCString* filename,float radius);

	void onEnterTransitionDidFinish();
	void onExit();
	void update(float dt);

	virtual bool ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent);
	virtual void ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent);

	void updateDirectionForTouchLocation(CCPoint location);

	CC_SYNTHESIZE(DPadDelegate* ,_delegate,Delegate);
	CC_SYNTHESIZE(bool,_isHeld,IsHeld);

protected:
	float _radius;
	CCPoint _direction;
	float _acce;
};

