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
#include "BigBullet.h"
//#include "SimpleAudioEngine.h"


using namespace cocos2d;

Ship* Ship::sharedShip=NULL;

Ship::Ship()
{

}

Ship::~Ship()
{
	
}

bool Ship::initWithFile(const char* pic)
{
	bool sRet=false;
	do{
		CC_BREAK_IF(!Unit::init());
		m_active=true;
		m_HP=2;
		m_canBeAttack=false;
		//add ship png
		CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage(pic);
        CCRect rec=CCRectMake(0,0,60,45);
		this->initWithTexture(pTexture,rec);
		this->setRotation(90);
		this->setPosition(ccp(50,160));

		CCSpriteFrame* frame0=CCSpriteFrame::createWithTexture(pTexture,CCRectMake(0,0,60,45));
		CCSpriteFrame* frame1=CCSpriteFrame::createWithTexture(pTexture,CCRectMake(60,0,60,45));

		CCArray* animFrames=CCArray::create();
		animFrames->addObject(frame0);
		animFrames->addObject(frame1);

		CCAnimation* animation=CCAnimation::createWithSpriteFrames(animFrames,0.1f);
		CCAnimate* animate=CCAnimate::create(animation);
		this->runAction(CCRepeatForever::create(animate));
		this->schedule(schedule_selector(Ship::shoot),0.1f);

		//revive ship
		CCSprite* ghost=CCSprite::createWithTexture(pTexture,CCRectMake(0,0,60,45));
		ccBlendFunc cb1={GL_SRC_ALPHA,GL_ONE};
		ghost->setBlendFunc(cb1);
		ghost->setPosition(ccp(this->getContentSize().width/2, 17));
		ghost->setScale(8);
		this->addChild(ghost,1,9999);
		ghost->runAction(CCScaleTo::create(0.5,1,1));
		//blink effect
		CCBlink* blink=CCBlink::create(3,9);

		CCCallFuncN* makeBeAttack=CCCallFuncN::create(this,callfuncN_selector(Ship::makeAttack));
		this->runAction(CCSequence::create(CCDelayTime::create(0.5),blink,makeBeAttack,NULL));

	/*
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

		this->schedule(schedule_selector(Ship::shoot),0.3f);
		*/
		sRet=true;
	}while(0);
	return sRet;
}

Ship *Ship::create(const char* pic)
{
	Ship *pRet=new Ship();
	if(pRet&&pRet->initWithFile(pic))
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


CCRect Ship::Rect()
{
	return CCRectMake(
		this->getPosition().x-(this->getContentSize().width/2),
		this->getPosition().y-(this->getContentSize().height/2),
		45,
		50);
}


void Ship::moveTo(CCPoint p)
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    CCRect winRect=CCRectMake(0,0,winSize.width,winSize.height);
	if(winRect.containsPoint(p)){
	this->setPosition(p);
	}
}



void Ship::hurt()
{
	if(m_canBeAttack)
	{
	m_HP--;
	this->setColor(ccc3(255,0,0));
	}
}

void Ship::update(float dt)
{
	if(m_HP<=0)
		m_active=false;

}


bool Ship::isActive()
{
	return m_active;
}


void Ship::destroy()
{
	Config::sharedConfig()->setShipHP();
	Effect* effect=Effect::create();
	effect->explode(this->getParent(),this->getPosition());
	this->removeFromParent();
	
}

void Ship::GOCallBack(CCNode* pSender)
{
	GameOverScene* gameoverscene=GameOverScene::create();
	char score[10];
	sprintf(score,"%06d",Config::sharedConfig()->getScore());
	gameoverscene->getlayer()->getlabel()->setString(score);
 
   if(!Config::sharedConfig()->highScore->getBoolForKey("isExisted"))  
   {  
        //do somthing when init the xml
	   Config::sharedConfig()->highScore->setIntegerForKey("highScore",Config::sharedConfig()->getScore());
	   Config::sharedConfig()->highScore->setBoolForKey("isExisted",true);  
   }else{
	    if(Config::sharedConfig()->highScore->getIntegerForKey("highScore")<Config::sharedConfig()->getScore())
	       {
	          Config::sharedConfig()->highScore->setIntegerForKey("highScore",Config::sharedConfig()->getScore());
	       }
   }
   char c[25]="highest score: ";
   char highscore[10];
   sprintf(highscore,"%06d",Config::sharedConfig()->highScore->getIntegerForKey("highScore"));
   gameoverscene->getlayer()->highScoreLabel->setString(strcat(c,highscore));
   CCDirector::sharedDirector()->replaceScene(gameoverscene);

}

void Ship::shoot(float dt)
{
	CCPoint position=this->getPosition();
	BigBullet* bigBullet=BigBullet::create("W1.png",700);   // in plist 2 kind of texture are W1.png and W2.png
	bigBullet->setRotation(90);
	if(bigBullet){
		m_allBigBulletArray->addObject(bigBullet);
		getParent()->addChild(bigBullet,1000,777);
		bigBullet->setPosition(ccp(position.x+30,position.y+10));
	}else{
		delete bigBullet;
		bigBullet=0;
	}

	BigBullet* bigBullet2=BigBullet::create("W1.png",700);
	bigBullet2->setRotation(90);
	if(bigBullet2){
		m_allBigBulletArray->addObject(bigBullet2);
		getParent()->addChild(bigBullet2,1000,777);
		bigBullet2->setPosition(ccp(position.x+30,position.y-10));
	}else{
		delete bigBullet2;
		bigBullet2=0;
	}
}


void Ship::makeAttack(CCNode* pSender)
{
	this->m_canBeAttack=true;
	this->setVisible(true);
	pSender->removeChildByTag(9999);
}