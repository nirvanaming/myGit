//
//HudLayer.cpp
//
//created by Tim on Oct 21st 2013
//
#include "HudLayer.h"
#include "Defines.h"
#include "Hero.h"
#include "Config.h"


HudLayer::HudLayer(void)
{
	_dpad=NULL;
	_rdpad=NULL;
	_scoreLabel=NULL;
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
		this->initScoreLabel();
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


void HudLayer::update(float dt)
{
	this->updateScoreLabel();
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


void HudLayer::initScoreLabel()
{
	_scoreLabel=CCLabelAtlas::create("1:","set1_player_hud3.png",14,21,'0');
	this->addChild(_scoreLabel);
	char score1[50];
	sprintf(score1,"%d",Config::sharedConfig()->getScore());
	_scoreLabel->setPosition(ccp(SCREEN.width-50,SCREEN.height-25));
	_scoreLabel->setString(score1);
}


void HudLayer::updateScoreLabel()
{
	char score[50];
	sprintf(score, "%d", Config::sharedConfig()->getScore());
	//int a=Config::sharedConfig()->getScore();
	//itoa(Config::sharedConfig()->getScore(),score,10);
	_scoreLabel->setString(score);
	//CCLog("%d",a);
}