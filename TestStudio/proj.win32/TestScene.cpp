//
//TestScene.cpp
//
//created by Tim on Nov 24th 2013
//
#include "TestScene.h"
#include "GameScene.h"


TestScene::TestScene(void)
{
}


TestScene::~TestScene(void)
{
}

CCScene* TestScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		scene = CCScene::create();
		CC_BREAK_IF(! scene);
		TestScene *layer = TestScene::create();
		CC_BREAK_IF(! layer);
		scene->addChild(layer);
	} while (0);
	return scene;
}



bool TestScene::init()
{
	bool bRet=false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		CCSprite* bg=CCSprite::create("HelloWorld.png");
		bg->setAnchorPoint(ccp(0.5,0.5));
		bg->setPosition(ccp(winSize.width/2,winSize.height/2));
		bg->setScale(2.0);
		this->addChild(bg,0,100);

		CCLabelTTF* label=CCLabelTTF::create("return","Arial",40);
		CCMenuItemLabel* returnItem=CCMenuItemLabel::create(label,this,menu_selector(TestScene::gameLayerCallBack));
		CCMenu* menu=CCMenu::create(returnItem,NULL);
		menu->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(menu,1,101);

		bRet=true;
	} while (0);
	return bRet;
}



void TestScene::gameLayerCallBack(CCObject* pSender)
{
	CCScene* pScene=GameScene::create();
	CCDirector::sharedDirector()->replaceScene(pScene);
}