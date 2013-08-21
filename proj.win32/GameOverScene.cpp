#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "Menu.h"

using namespace cocos2d;

bool GameOverScene::init()
{
	if(CCScene::init())
	{
		this->_layer=GameOverLayer::create();
		this->_layer->retain();
		this->addChild(_layer);

		return true;
	}
	else
	{
		return false;
	}
}

GameOverScene::~GameOverScene()
{
	if(_layer)
	{
		_layer->release();
		_layer=NULL;
	}
}

bool GameOverLayer::init()
{
	if(CCLayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		//add the background
		 CCSprite* pSprite = CCSprite::create("Download/SkyWardBG2.png");
       // CC_BREAK_IF(! pSprite);
        pSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(pSprite, 0);

		this->_label=CCLabelTTF::create("","Broadway",32);
		_label->retain();
		_label->setColor(ccc3(200,200,200));
		_label->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(_label);

		CCLabelTTF *pLabel=CCLabelTTF::create("Please press 'confirm' to play again!","Aharoni",20);
		pLabel->setPosition(ccp(winSize.width/2,winSize.height/2-30));
		pLabel->setColor(ccc3(150,150,150));
		this->addChild(pLabel);

		//****************************************Ìí¼ÓµÄplay again°´Å¥

		   CCMenuItemImage *pPlayAgainItem = CCMenuItemImage::create(
            "Download/Confirm1.png",
            "Download/Confirm2.png",
            this,
			menu_selector(GameOverLayer::PlayScreenCallBack));
      //  CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pPlayAgainItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 100, 40));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pPlayAgainItem, NULL);
        pMenu->setPosition(CCPointZero);
      //  CC_BREAK_IF(! pMenu);

        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

		//***************************************
		/*
		this->runAction(CCSequence::create(
			CCDelayTime::create(3),
			CCCallFunc::create(this,
			callfunc_selector(GameOverLayer::gameOverDone)),
			NULL));
			*/
		return true;
	}
	else
	{
		return false;
	}
}

void GameOverLayer::gameOverDone()
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void GameOverLayer::PlayScreenCallBack(CCObject *pSender)
{
	CCScene* pScene=HelloWorld::scene();
	//CCScene* pScene2=new SettingScene;
	//CCDirector::sharedDirector()->replaceScene(CCTransitionRotoZoom::create(2,pScene));
	CCDirector::sharedDirector()->replaceScene(pScene);

}

GameOverLayer::~GameOverLayer()
{
	if(_label)
	{
		_label->release();
		_label=NULL;
	}
}
