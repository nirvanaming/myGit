#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include "Menu.h"
#include "Config.h"

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
	bool bRect=false;

	do{
	if(CCLayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		CCSize winSize=CCDirector::sharedDirector()->getWinSize();

		//add the background
		 CCSprite* pSprite = CCSprite::create("Download/SkyWardBG2.png");
       // CC_BREAK_IF(! pSprite);
        pSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
        this->addChild(pSprite, 0);

		this->_label=CCLabelTTF::create("","FZCuYuan-M03",40);
		_label->retain();
		_label->setColor(ccc3(200,200,200));
		_label->setPosition(ccp(winSize.width/2,winSize.height/2));
		this->addChild(_label);
		
		CCLabelTTF* gameoverlabel=CCLabelTTF::create("Game Over","Aharoni",40);
		gameoverlabel->setColor(ccc3(150,150,150));
		gameoverlabel->setPosition(ccp(winSize.width/2,winSize.height/2+50));
		this->addChild(gameoverlabel);
		//add your score label
		CCLabelTTF*  scoreLabel=CCLabelTTF::create("Your score is: ","FZCuYuan-M03",20);
		//scoreLabel->setAnchorPoint(ccp(0,0));
		scoreLabel->setColor(ccc3(150,150,150));
		scoreLabel->setPosition(ccp(winSize.width/2,winSize.height/2+30));
		this->addChild(scoreLabel);

		//add confirm label
		CCLabelTTF* pLabel=CCLabelTTF::create("Please press 'confirm' to play again!","Aharoni",20);
		pLabel->setPosition(ccp(winSize.width/2,winSize.height/2-30));
		pLabel->setColor(ccc3(150,150,150));
		this->addChild(pLabel);

		//****************************************add "play again" button

		   CCMenuItemImage *pPlayAgainItem = CCMenuItemImage::create(
            "Download/Confirm1.png",
            "Download/Confirm2.png",
            this,
			menu_selector(GameOverLayer::PlayScreenCallBack));
      //  CC_BREAK_IF(! pCloseItem);
        pPlayAgainItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 100, 40));
        CCMenu* pMenu = CCMenu::create(pPlayAgainItem, NULL);
        pMenu->setPosition(CCPointZero);
        //CC_BREAK_IF(! pMenu);
        this->addChild(pMenu, 1);
	}
	bRect= true;
	}while(0);


	return bRect;
}

void GameOverLayer::gameOverDone()
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void GameOverLayer::PlayScreenCallBack(CCObject *pSender)
{
	CCScene* pScene=HelloWorld::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
	Config::sharedConfig()->resetConfig();

}

GameOverLayer::~GameOverLayer()
{
	if(_label)
	{
		_label->release();
		_label=NULL;
	}
}
