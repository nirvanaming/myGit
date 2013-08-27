//
//Ship.cpp
//
//created by Tim on Aug 16th 2013
//

#include "Ship.h"
#include "Effect.h"
#include "GameOverScene.h"
#include "string.h"
#include "Config.h"

using namespace cocos2d;

Ship* Ship::sharedShip=NULL;

Ship::Ship()
	//shipHP(3)
{

}

Ship::~Ship()
{

}

bool Ship::init()
{
	bool sRet=false;
	do{
		CC_BREAK_IF(!CCLayer::init());
		//add ship png
		CCSprite* sShip=CCSprite::create("Player.png",CCRectMake(47*2,0,47,56));
		this->addChild(sShip,0,747);
		/////////create animation//////////////////////////////////
		CCAnimation* animation=CCAnimation::create();
		animation->setDelayPerUnit(0.1f);
		//define every frame of animation
		for(unsigned int i=0;i<4;i++)
		{
			animation->addSpriteFrame(
				CCSpriteFrame::create("Player.png",CCRectMake(47*i,0,47,56)));

		}
		//create animation
		CCAnimate* anim=CCAnimate::create(animation);
		sShip->runAction(::cocos2d::CCRepeatForever::create(anim));
		sShip->setPosition(ccp(50,160));
		sShip->setRotation(90);

		


		sRet=true;
	}while(0);
	return sRet;
}

Ship *Ship::create()
{
	Ship *pRet=new Ship();
	if(pRet&&pRet->init())
	{
		pRet->autorelease();
		sharedShip=pRet;
		return pRet;
	}

	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}


CCRect Ship::shipRect()
{
	return CCRectMake(
		          	this->getChildByTag(747)->getPosition().x-(this->getChildByTag(747)->getContentSize().width/2),
		          	this->getChildByTag(747)->getPosition().y-(this->getChildByTag(747)->getContentSize().height/2),
			        this->getChildByTag(747)->getContentSize().width,
		          	this->getChildByTag(747)->getContentSize().height);
}



void Ship::moveTo(CCPoint p)
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    CCRect winRect=CCRectMake(0,0,winSize.width,winSize.height);
	if(winRect.containsPoint(p)){
	this->getChildByTag(747)->setPosition(p);
	}
}



void Ship::Hurt()
{
	Config::sharedConfig()->setShipHP();
	Effect* effect=Effect::create();
	effect->explode(this->getParent(),this->getChildByTag(747)->getPosition());
	
	if(Config::sharedConfig()->shipHP<=0)
	{
        CCCallFuncN *goCallBack = CCCallFuncN::create(this, callfuncN_selector(Ship::GOCallBack));
        this->runAction(CCSequence::create(CCDelayTime::create(0.5), goCallBack, NULL));
	}
}


void Ship::GOCallBack(CCNode* pSender)
{
	GameOverScene* gameoverscene=GameOverScene::create();
	    gameoverscene->getlayer()->getlabel()->setString("YouLose :<");
	    CCDirector::sharedDirector()->replaceScene(gameoverscene);

}