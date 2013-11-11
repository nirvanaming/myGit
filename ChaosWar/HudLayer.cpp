//
//HudLayer.cpp
//
//created by Tim on Oct 21st 2013
//
#include "HudLayer.h"
#include "Defines.h"
#include "Hero.h"


HudLayer::HudLayer(void)
{
	_dpad=NULL;
	_rdpad=NULL;
}


HudLayer::~HudLayer(void)
{
}


bool HudLayer::init()
{
	bool bRet=false;
	do{
		CC_BREAK_IF(!CCLayer::init());

		this->initDpad();
		this->scheduleUpdate();

		bRet=true;
	}while(0);
	return bRet;

}


void HudLayer::initDpad()
{
	    _dpad = DPad::create(CCString::create("pd_dpad.png"), 64.0f);
		CCAssert(_dpad!=NULL,"pd_dpad.png not found");
		_dpad->setPosition(ccp(64.0f,64.0f));
		_dpad->setOpacity(100);
		this->addChild(_dpad);

		_rdpad=RightDPad::create(CCString::create("pd_dpad.png"),64.0f);
		CCAssert(_rdpad!=NULL,"pd_dpad.png not found");
		_rdpad->setPosition(ccp(SCREEN.width-64.0f,64.0f));
		_rdpad->setOpacity(100);
		this->addChild(_rdpad);
}

void HudLayer::draw()
{
	CCLayer::draw();
	ccDrawColor4F(0,0,0,255);
	glLineWidth(5);
	ccDrawLine(CCPointMake(13,SCREEN.height-8),CCPointMake(13+10*Hero::sharedHero()->getMaxHP(),SCREEN.height-8));
	ccDrawColor4F(0,255,0,255);
	glLineWidth(5);
	ccDrawLine(CCPointMake(10,SCREEN.height-11),CCPointMake(10+10*Hero::sharedHero()->getHP(),SCREEN.height-11));
}


