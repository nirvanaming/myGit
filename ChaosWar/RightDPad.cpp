//
//RDpad.cpp
//
//created by Tim on Oct 27th 2013
//
#include "RightDPad.h"
USING_NS_CC;

RightDPad::RightDPad(void)
{
	_rdelegate=NULL;
}


RightDPad::~RightDPad(void)
{
}


RightDPad* RightDPad::create(CCString* fileName,float radius)
{
	RightDPad* pRet=new RightDPad();
	if(pRet && pRet->initWithFile(fileName,radius))
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


bool RightDPad::initWithFile(CCString *fileName, float radius)
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCSprite::initWithFile(fileName->getCString()));

		_radius=radius;
		_direction=CCPointZero;
		_isHelding=false;

		this->scheduleUpdate();

		bRet=true;
	}while(0);
	return bRet;
}



void RightDPad::onEnterTransitionDidFinish()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,1,true);
}


void RightDPad::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


void RightDPad::update(float dt)
{
	if(_isHelding)
	{
		_rdelegate->isHoldingRotation(this,_degree,_to_direction);
	}
}


bool RightDPad::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	CCPoint location=pTouch->getLocation();
	float distanceSQ=ccpDistanceSQ(location,this->getPosition());
	if(distanceSQ<=_radius*_radius)
	{
		this->updateRDirectionForTouchLocation(location);
		_isHelding=true;
		return true;
	}
	return false;
}


void RightDPad::ccTouchMoved(CCTouch* pTouch, CCEvent *pEvent)
{
	CCPoint location=pTouch->getLocation();
	this->updateRDirectionForTouchLocation(location);
}

void RightDPad::ccTouchEnded(CCTouch* pTouch,CCEvent* pEvent)
{
	_direction=CCPointZero;
	_isHelding=false;
	_rdelegate->RightDPadTouchEnded(this);
}


void RightDPad::updateRDirectionForTouchLocation(CCPoint location)
{
	_direction=ccpNormalize(ccpSub(this->getPosition(),location));
	_to_direction=ccpNormalize(ccpSub(location,this->getPosition()));
	_degree=CC_RADIANS_TO_DEGREES(atan2(_direction.y, - _direction.x));
	//_degree=CC_RADIANS_TO_DEGREES(ccpToAngle(_direction));

	_rdelegate->didChangeRotationTo(this,_degree,_to_direction);
}