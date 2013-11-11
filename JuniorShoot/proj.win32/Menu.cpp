
#include "Menu.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

/*
CCScene* MenuLayer::scene()
{
	
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
	MenuLayer *layer = MenuLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool MenuLayer::init()
{
	//1.
	if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	 //2.
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "Download/GoButton1.png",
                                        "Download/GOButton2.png",
                                        this,
                                        menu_selector(MenuLayer::HelloWorldCallBack));

   
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

	//3.
	//add background
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pSprite=CCSprite::create("Download/sunset.jpg");
	//CC_BREAK_IF(!pSprite);
	pSprite->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(pSprite,0);

	//add label
	CCLabelTTF* pLabel=CCLabelTTF::create("Please PUSH the lower right coner BUTTON to start the game","Arial",15);
	pLabel->setColor(ccc3(100,100,100));
	//CC_BREAK_IF(!pLabel);
	pLabel->setPosition(ccp(size.width/2,size.height/2+100));
	this->addChild(pLabel,2);

}


void MenuLayer::HelloWorldCallBack(CCObject* pSender)
{
	CCScene* pScene = new HelloWorld();

	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX());
}

*/

MenuLayer::MenuLayer()
{   
	//button
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "Download/GoButton1.png",
                                        "Download/GOButton2.png",
                                        this,
                                        menu_selector(MenuLayer::HelloWorldCallBack));
    pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
	//add background
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite* pSprite=CCSprite::create("Download/sunset.jpg");
	pSprite->setPosition(ccp(size.width/2,size.height/2));
	this->addChild(pSprite,0);
	CCLabelTTF* pLabel=CCLabelTTF::create("Please PUSH the lower right coner BUTTON to start the game","Arial",15);
	pLabel->setColor(ccc3(100,100,100));
	pLabel->setPosition(ccp(size.width/2,size.height/2+100));
	this->addChild(pLabel,2);

}

MenuLayer::~MenuLayer()
{}


SettingScene::SettingScene()
{}
SettingScene::~SettingScene()
{}
void SettingScene::onEnter()
{
	CCScene::onEnter();
	CCLayer* pLayer=new MenuLayer();
	this->addChild(pLayer);
	pLayer->release();
}


void MenuLayer::HelloWorldCallBack(CCObject* pSender)
{
	CCScene* pScene=HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFlipAngular::create(1.0f,pScene));
}
