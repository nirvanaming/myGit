//
//HelloWorldScene.cpp
//
//created by Tim on Aug 8th 2013
//
#include "HelloWorldScene.h"
//#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "Menu.h"
#include "DialogLayer.h"
#include "PauseLayer.h"
#include "Ship.h"
#include "Enemy.h"
#include "Effect.h"
#include "Config.h"
#include "BigBullet.h"
#include "Unit.h"


using namespace std;
using namespace cocos2d;


HelloWorld::HelloWorld()
	:pSpriteWidth(0)
	,m_ispSpriteReload(false)
	,mIsTouching(false)
    ,m_scoreLabel(NULL)
    ,m_lifeCountLabel(NULL){}

HelloWorld::~HelloWorld()
{
	if(m_EnemyActionMag)
	{
		delete m_EnemyActionMag;
	}
	m_allBigBulletArray->release();
	m_allEnemyBulletArray->release();
	m_allEnemyArray->release();
}

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    return scene;
}


bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        CC_BREAK_IF(! CCLayer::init());
		m_allBigBulletArray=CCArray::create();
        m_allBigBulletArray->retain();

		m_allEnemyArray=CCArray::create();
		m_allEnemyArray->retain();

		m_allEnemyBulletArray=CCArray::create();
		m_allEnemyBulletArray->retain();

        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
     
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
        this->addChild(pMenu, 1);

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		m_screenRect=CCRectMake(0,0,size.width+30,size.height);

		//*********************************************************************************
		Enemy::sharedEnemy();
		m_EnemyActionMag=new EnemyActionMag(this);

		//add pause button£º*******************************************************/
		CCMenuItemImage* pauseBtn=CCMenuItemImage::create
			("Download/Pause.png","Download/Pause.png",NULL,
			this,menu_selector(HelloWorld::pauseLayerCallback));

		CCMenu* menu=CCMenu::create(pauseBtn,NULL);
		menu->setPosition(ccp(size.width-50,size.height-50));
		menu->setTag(10);           //set a tag, using to hide
		this->addChild(menu,100);

        // 3. Add a splash screen, show the cocos2d splash image.
        pSprite = CCSprite::create("Download/BackSky.png");
		pSprite->setAnchorPoint(ccp(0,0));  //set the display center point
		pSpriteWidth=pSprite->getContentSize().width;
        CC_BREAK_IF(! pSprite);
        // Place the sprite on the center of the screen
        pSprite->setPosition(ccp(0, 0));
        // Add the sprite to HelloWorld layer as a child layer.
        this->addChild(pSprite, -10);
		pSprite->runAction(CCMoveBy::create(3,ccp(-240,0)));
		this->schedule(schedule_selector(HelloWorld::movingBackground),3);
	    //add ship
		this->m_ship=Ship::create("ship01.png");
		this->addChild(m_ship,1,999);
	  
		//score label
		char score[20];
        char s[30] = "score:";
		sprintf(score,"%06d",Config::sharedConfig()->getScore());
		m_scoreLabel = CCLabelTTF::create(strcat(s,score), "FZCuYuan-M03", 20);
		CC_BREAK_IF(! m_scoreLabel);
		m_scoreLabel->setAnchorPoint(ccp(0,0));
		m_scoreLabel->setPosition(ccp(20, size.height-30));
		m_scoreLabel->setColor(ccc3(255,0,0));
		this->addChild(m_scoreLabel, 1);
		//ship life count label
		char lifecount[3];
		char c[30]="life:";
		sprintf(lifecount,"%02d",Config::sharedConfig()->getShipHP());
		m_lifeCountLabel=CCLabelTTF::create(strcat(c,lifecount),"FZCuYuan-M03",20);
		CC_BREAK_IF(!m_lifeCountLabel);
		m_lifeCountLabel->setAnchorPoint(ccp(0,0));
		m_lifeCountLabel->setPosition(ccp(20,size.height-50));
		m_lifeCountLabel->setColor(ccc3(255,0,0));
		this->addChild(m_lifeCountLabel,1);
		
		CCSpriteBatchNode* icon=CCSpriteBatchNode::create("Download/icon.png");
		CCSprite* shipIcon1=CCSprite::createWithTexture(icon->getTexture());
		shipIcon1->setPosition(ccp(m_lifeCountLabel->getPosition().x+65,m_lifeCountLabel->getPosition().y+12));
		icon->addChild(shipIcon1,1,101);
		CCSprite* shipIcon2=CCSprite::createWithTexture(icon->getTexture());
		shipIcon2->setPosition(ccp(m_lifeCountLabel->getPosition().x+80,m_lifeCountLabel->getPosition().y+12));
		icon->addChild(shipIcon2,1,102);
		CCSprite* shipIcon3=CCSprite::createWithTexture(icon->getTexture());
		shipIcon3->setPosition(ccp(m_lifeCountLabel->getPosition().x+95,m_lifeCountLabel->getPosition().y+12));
		icon->addChild(shipIcon3,1,103);
		addChild(icon,4,100);

		scheduleUpdate();
		schedule(schedule_selector(HelloWorld::scoreCounter), 1.0f);
		
		//this->schedule(schedule_selector(HelloWorld::addEnemy),0.7f);
	
		setTouchEnabled(true);

		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		//	"background-music-aac.wav",true);
        bRet = true;
    } while (0);

    return bRet;
}



void HelloWorld::isCollide()
{
	
	CCObject* enemys;
	CCObject* shipBullets;
	CCObject* enemyBullets;
	
	CCARRAY_FOREACH(m_allEnemyArray,enemys)
	{
		Unit* enemy=dynamic_cast<Unit*>(enemys);
		Unit* ship=dynamic_cast<Unit*>(m_ship);
		
		CCARRAY_FOREACH(m_allBigBulletArray,shipBullets)
		{
			Unit* bullet=dynamic_cast<Unit*>(shipBullets);
			if(this->collide(enemy,bullet))
			{
				enemy->hurt();
				bullet->hurt();
			}
			if(!(m_screenRect.intersectsRect(bullet->boundingBox())))
			{
				m_allBigBulletArray->removeObject(bullet);
				bullet->removeFromParent();
				
			}
		}
		if(collide(enemy,m_ship))
		{
			if(m_ship->isActive())
			{
				enemy->hurt();
				m_ship->hurt();
			}
	     }
		if(!(m_screenRect.intersectsRect(enemy->boundingBox())))
		{
			m_allEnemyArray->removeObject(enemy);
			enemy->removeFromParent();
			//enemy->destroy();
		}
	}

	CCARRAY_FOREACH(m_allEnemyBulletArray,enemyBullets)
	{
		Unit* enemyB=dynamic_cast<Unit*>(enemyBullets);
		if(enemyB)		{
			if(collide(enemyB,m_ship))
			{
				if(m_ship->isActive())
			  {
				enemyB->hurt();
				m_ship->hurt();
			  }
			}
			if(!m_screenRect.intersectsRect(enemyB->boundingBox()))
			{
				m_allEnemyBulletArray->removeObject(enemyB);
				enemyB->removeFromParent();
				//enemyB->destroy();
			}
		}
	}	
}

bool HelloWorld::collide(Unit* a, Unit* b)
{
	if(!a||!b)
	{
		return false;
	}
	CCRect aRect=a->Rect();
	CCRect bRect=b->Rect();
	if(aRect.intersectsRect(bRect))
	{
		return true;
	}
	return false;
}


void HelloWorld::update(float dt)
{
	isCollide();
	updateUI();
	checkReborn();
	removeInactiveUnit(dt);
}



void HelloWorld::removeInactiveUnit(float dt)
{
	
	CCArray* children=this->getChildren();
	for(unsigned int i=0; i<children->count();i++)
	{
		CCSprite* child=dynamic_cast<CCSprite*>(children->objectAtIndex(i));
		if(child)
		{
			child->update(dt);
			int tag=child->getTag();
			if(tag==777||tag==888||tag==666)   //shipbullet:777, enemy:888, ship:999,enemybullet:666
			{
				if(!((Unit*)child)->isActive())
			   {
				((Unit*)child)->destroy();
			   }
			}

        }
	}
	if(m_ship)
	{
		if(!m_ship->isActive())
		{
			m_ship->destroy();
			m_ship=NULL;
		}	
	}
}
 
	
//close Layer call back
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    //CCDirector::sharedDirector()->end();
	CCDirector::sharedDirector()->pause();
	DialogLayer *dialogLayer = DialogLayer::create();
    this->addChild(dialogLayer);

}

//pause Layer call back
void HelloWorld::pauseLayerCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->pause();
	PauseLayer* pauseLayer=PauseLayer::create();
	this->getChildByTag(10)->setVisible(false);   
	this->addChild(pauseLayer);
}

//background rolling call back
void HelloWorld::movingBackground(float dt)
{
	
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	pSprite->runAction(CCMoveBy::create(3,ccp(-240,0)));
	pSpriteWidth-=240.0;
	if(pSpriteWidth<=winSize.width)
	{
		if(!m_ispSpriteReload)
		{
			m_pSpriteRe=CCSprite::create("Download/BackSky.png");
			m_pSpriteRe->setAnchorPoint(ccp(0,0));
			this->addChild(m_pSpriteRe,-10);
			m_pSpriteRe->setPosition(ccp(winSize.width,0));
			m_ispSpriteReload=true;
		}
		m_pSpriteRe->runAction(CCMoveBy::create(3,ccp(-240,0)));
	}

	if(pSpriteWidth<=0)
	{
		pSpriteWidth=pSprite->getContentSize().width;
		this->removeChild(pSprite,true);
		pSprite=m_pSpriteRe;
		m_pSpriteRe=NULL;
		m_ispSpriteReload=false;
	}
}


//update score and hp
void HelloWorld::updateUI()
{
	char score[20];
    char s[30] = "score:";
	sprintf(score, "%06d", Config::sharedConfig()->getScore());
	m_scoreLabel->setString(strcat(s,score));

	char lifecount[3];
	char c[30]="life:";
	sprintf(lifecount,"%02d",Config::sharedConfig()->getShipHP());
	m_lifeCountLabel->setString(strcat(c,lifecount));
	
	int hp=Config::sharedConfig()->getShipHP();
	switch(hp){
	case 3:
		break;
	case 2:
		this->getChildByTag(100)->getChildByTag(103)->setVisible(false);
		break;
	case 1:
		this->getChildByTag(100)->getChildByTag(102)->setVisible(false);
		break;
	case 0:
		this->getChildByTag(100)->getChildByTag(101)->setVisible(false);
		break;
	}
}

/*
void HelloWorld::addEnemy(float dt)
{
	
	Enemy* spriteEnemy=Enemy::create("Download/HexPilot.png",1);
	spriteEnemy->setRotation(180);
	spriteEnemy->setScale(0.7f);
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minY=spriteEnemy->getContentSize().height/2;
	int maxY=winSize.height-spriteEnemy->getContentSize().height/2;
	int rangeY=maxY-minY;
	int actualY=(rand()%rangeY)+minY;
	spriteEnemy->setPosition(ccp(winSize.width+(spriteEnemy->getContentSize().width/2),actualY));
	this->addChild(spriteEnemy,1,888);
	spriteEnemy->move();
    m_allEnemyArray->addObject(spriteEnemy);

}
*/

void HelloWorld::checkReborn()
{
	
	if(Config::sharedConfig()->getShipHP()>0)
	{
		if(!m_ship)
		{
			m_ship=Ship::create("ship01.png");
			this->addChild(m_ship,2,999);
		}
	}
    else if(Config::sharedConfig()->getShipHP()<=0)
		{
			m_ship=NULL;
			CCCallFuncN *goCallBack = CCCallFuncN::create(this, callfuncN_selector(Ship::GOCallBack));
             this->runAction(CCSequence::create(CCDelayTime::create(0.5f), goCallBack, NULL));

		}
}

Ship* HelloWorld::getShip()
{
	return m_ship;
}


void HelloWorld::scoreCounter(float dt)
{
	m_time++;
	m_EnemyActionMag->loadResource(m_time);
}

void HelloWorld::onEnter()
{
	CCLayer::onEnter();  
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true); 
}


void HelloWorld::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}


bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	mTouchPos=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	if(m_ship)
	mIsTouching=true;

	return true;
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch *pTouch,cocos2d::CCEvent *pEvent)
{
	if(mIsTouching && m_ship){
		CCPoint touchPos=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
		CCPoint moveDelta=ccpSub(touchPos,mTouchPos);
		CCPoint nextPos=ccpAdd(m_ship->getPosition(),moveDelta);

		CCSize winSize=CCDirector::sharedDirector()->getWinSize();
		CCRect winRect=CCRectMake(0,0,winSize.width,winSize.height);
		
		if(winRect.containsPoint(nextPos)){
			this->m_ship->moveTo(nextPos);
		}
		mTouchPos=touchPos;
	}
}


void HelloWorld::ccTouchEnded(cocos2d::CCTouch *pTouch,cocos2d::CCEvent *pEvent)
{
	mIsTouching=false;
}

void HelloWorld::ccTouchCancelled(cocos2d::CCTouch *pTouch,cocos2d::CCEvent *pEvent)
{
	mIsTouching=false;
}
