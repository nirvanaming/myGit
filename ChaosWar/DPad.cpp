//
//DPad.cpp
//
//created by Tim on Oct 21st 2013
//
#include "DPad.h"
USING_NS_CC;


DPad::DPad(void)
{
	_delegate=NULL;
}


DPad::~DPad(void)
{
}


DPad* DPad::create(CCString* filename, float radius)
{
	DPad* pRet=new DPad();
	if(pRet && pRet->initWithFile(filename,radius))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool DPad::initWithFile(CCString* filename,float radius)
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCSprite::initWithFile(filename->getCString()));
		_radius=radius;
		_direction=CCPointZero;
		_isHeld=false;
		this->scheduleUpdate();

		bRet=true;
	}while(0);
	return bRet;
}



void DPad::onEnterTransitionDidFinish()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,true);
}

void DPad::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


void DPad::update(float dt)
{
	if(_isHeld)
	{
		_delegate->isHoldingDirection(this,_direction,_acce);
	}
}


bool DPad::ccTouchBegan(CCTouch* pTouch,CCEvent* pEvent)
{
	CCPoint location=pTouch->getLocation();

	float distanceCQ=ccpDistanceSQ(location,this->getPosition());
	if(distanceCQ<=_radius*_radius)
	{
		this->updateDirectionForTouchLocation(location);
		_isHeld=true;
		return true;
	}
	return false;
}


void DPad::ccTouchMoved(CCTouch* pTouch,CCEvent* pEvent)
{
	CCPoint location=pTouch->getLocation();
	this->updateDirectionForTouchLocation(location);
}


void DPad::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
	_direction=CCPointZero;
	_isHeld=false;
	_delegate->simpleDPadTouchEnded(this);

}


void DPad::updateDirectionForTouchLocation(CCPoint location)
{

	/*float radius=ccpToAngle(ccpSub(location,this->getPosition()));
	float degree=-1*CC_RADIANS_TO_DEGREES(radius);

	if(degree<=22.5&&degree>=-22.5)
	{
		_direction=ccp(1.0,0.0);
	}
	else if(degree>22.5&&degree<67.5)
	{
		_direction=ccp(1.0,-1.0);
	}
	else if(degree>=67.5&&degree<=112.5)
	{
		_direction=ccp(0.0,-1.0);
	}
	else if(degree>112.5&&degree<157.5)
	{
		_direction=ccp(-1.0,-1.0);
	}
	else if(degree>=157.5||degree<=-157.5)
	{
		_direction=ccp(-1.0,0.0);
	}
	else if(degree<-22.5&&degree>-67.5)
	{
		_direction=ccp(1.0,1.0);
	}
	else if(degree<=-67.5&&degree>=-112.5)
	{
		_direction=ccp(0.0,1.0);
	}
	else if(degree<-112.5&&degree>-157.5)
	{
		_direction=ccp(-1.0,1.0);
	}*/

	_direction=ccpNormalize(ccpSub(location,this->getPosition()));
	_acce=ccpDistance(this->getPosition(), location); 
	_delegate->didChangeDirectionTo(this,_direction,_acce);
}