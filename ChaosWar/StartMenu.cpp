//
//StartMenu.cpp
//
//created by Tim on Nov 4th 2013
//
#include "StartMenu.h"
#include "GameScene.h"
USING_NS_CC;


StartMenu::StartMenu(void)
{
}


StartMenu::~StartMenu(void)
{
}


CCScene* StartMenu::scene()
{
	CCScene* scene=CCScene::create();
	StartMenu* layer=StartMenu::create();
	scene->addChild(layer);
	return scene;
}



bool StartMenu::init()
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		CCSprite* bg=CCSprite::create("HelloWorld.png");
		CCAssert(bg!=NULL, "HelloWorld not found");
		bg->setAnchorPoint(ccp(0,0));
		bg->setPosition(ccp(0,0));
		this->addChild(bg,0,1);

		CCMenuItemImage* newGameMenu=CCMenuItemImage::create("btn-play-normal.png",
			"btn-play-selected.png",
			this,
			menu_selector(StartMenu::newGame));
		CCAssert(newGameMenu!=NULL,"btn-play-normal.png not found");
		newGameMenu->setPosition(ccp(origin.x + visibleSize.width - newGameMenu->getContentSize().width/2 ,
			origin.y + newGameMenu->getContentSize().height/2));

		CCMenu* pMenu=CCMenu::create(newGameMenu,NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu,1);

		bRet=true;
	}while(0);
	return bRet;
}



void StartMenu::newGame(CCObject* pSnder)
{
	CCScene* scene=GameScene::create();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, scene));
}
