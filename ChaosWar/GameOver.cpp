//
//GameOver.cpp
//
//created by Tim on Nov 6th 2013
//
#include "GameOver.h"


GameOver::GameOver(void)
{
}


GameOver::~GameOver(void)
{
}


bool GameOver::init()
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		CCSprite* bg=CCSprite::create("HelloWorld.png");
		CCAssert(bg!=NULL, "HelloWorld.png not found");
		bg->setAnchorPoint(ccp(0,0));
		bg->setPosition(CCPointZero);
		this->addChild(bg,0);

		CCSprite* lose=CCSprite::create("lose.png");
		CCAssert(lose!=NULL, "lose.png not found");
		lose->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(lose,1);

		bRet=true;
	}while(0);
	return bRet;
}


CCScene* GameOver::createScene()
{
	CCScene* scene=CCScene::create();
	GameOver* layer=GameOver::create();
	scene->addChild(layer);
	return scene;
}