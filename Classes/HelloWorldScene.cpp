//
//HelloWorldScene.cpp
//
//created by Tim on Aug 8th 2013
//
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"
#include "Menu.h"
#include "DialogLayer.h"
#include "PauseLayer.h"
#include "Bullet.h"
#include "Ship.h"
#include "Enemy.h"
#include "Effect.h"
#include "Config.h"


using namespace std;
using namespace cocos2d;


HelloWorld::HelloWorld()
	:pSpriteWidth(0)
	,m_ispSpriteReload(false)
	,mIsTouching(false)
  //  ,Score(0)
    ,m_scoreLabel(NULL)
    ,m_lifeCountLabel(NULL){}

HelloWorld::~HelloWorld()
{
	
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

    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.
        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(HelloWorld::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));
        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);
        // Add the menu to HelloWorld layer as a child layer.
        this->addChild(pMenu, 1);

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		//add pause button£º*******************************************************/
		CCMenuItemImage* pauseBtn=CCMenuItemImage::create
			("Download/Pause.png","Download/Pause.png",NULL,
			this,menu_selector(HelloWorld::pauseLayerCallback));

		//pauseBtn->setAnchorPoint(ccp(1,1));
		CCMenu* menu=CCMenu::create(pauseBtn,NULL);
		menu->setPosition(ccp(size.width-50,size.height-50));
		menu->setTag(10);           //set a tag, using to hide
		this->addChild(menu,1);

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
		this->m_ship=Ship::create();
		this->addChild(m_ship);
	    //add bullets
		this->m_bullet=Bullet::create();
		this->addChild(m_bullet);
		//add enemy
		this->m_enemy=Enemy::create();
		this->addChild(m_enemy);

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
		shipIcon1=CCSprite::createWithTexture(icon->getTexture());
		shipIcon1->setPosition(ccp(m_lifeCountLabel->getPosition().x+65,m_lifeCountLabel->getPosition().y+12));
		icon->addChild(shipIcon1);

		shipIcon2=CCSprite::createWithTexture(icon->getTexture());
		shipIcon2->setPosition(ccp(m_lifeCountLabel->getPosition().x+80,m_lifeCountLabel->getPosition().y+12));
		icon->addChild(shipIcon2);

		shipIcon3=CCSprite::createWithTexture(icon->getTexture());
		shipIcon3->setPosition(ccp(m_lifeCountLabel->getPosition().x+95,m_lifeCountLabel->getPosition().y+12));
		icon->addChild(shipIcon3);

		addChild(icon,4);





		//call back func
		this->schedule(schedule_selector(HelloWorld::isCollide));
		this->schedule(schedule_selector(HelloWorld::updateUI),0.1f);
	
		setTouchEnabled(true);


		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		//	"background-music-aac.wav",true);
        bRet = true;
    } while (0);

    return bRet;
}



void HelloWorld::isCollide(float dt)
{
	for(unsigned int i=0;i<m_allEnemyBulletArray->count();i++)
	{
		CCSprite* nowEnemyBullet=(CCSprite*)m_allEnemyBulletArray->objectAtIndex(i);
		CCRect enemyBulletRect=CCRectMake(
			    nowEnemyBullet->getPosition().x-(nowEnemyBullet->getContentSize().width/2),
				nowEnemyBullet->getPosition().y-(nowEnemyBullet->getContentSize().height/2),
				nowEnemyBullet->getContentSize().width/2,
				nowEnemyBullet->getContentSize().height/2);

		if(enemyBulletRect.intersectsRect(m_ship->shipRect()))           //enemy bullet hit ship
		{
			m_ship->Hurt();
			m_allEnemyBulletArray->removeObject(nowEnemyBullet);
			nowEnemyBullet->removeFromParent();
		}



	}

	for(unsigned int i=0;i<m_allEnemyArray->count();i++)  //all enemies in screen
	{
		CCSprite* nowEnemy=(CCSprite*)m_allEnemyArray->objectAtIndex(i);
		   
		CCRect nowEnemyRect=CCRectMake(
				nowEnemy->getPosition().x-(nowEnemy->getContentSize().width/2),
				nowEnemy->getPosition().y-(nowEnemy->getContentSize().height/2),
				nowEnemy->getContentSize().width/2-10,
				nowEnemy->getContentSize().height/2-10);

		 if(nowEnemyRect.intersectsRect(m_ship->shipRect()))
			{
				m_ship->Hurt();
				m_allEnemyArray->removeObject(nowEnemy);
				nowEnemy->removeFromParent();
				Config::sharedConfig()->setScore(100);

			}

		for(unsigned int i=0;i<m_allPlayerBulletArray->count();i++)  //all bullets in screen
		{
			CCSprite* nowBullet=(CCSprite*)m_allPlayerBulletArray->objectAtIndex(i);
			CCRect nowBulletRect=CCRectMake(
		           	nowBullet->getPosition().x-(nowBullet->getContentSize().width/2),
		           	nowBullet->getPosition().y-(nowBullet->getContentSize().height/2),
			        nowBullet->getContentSize().width/2,
		          	nowBullet->getContentSize().height/2);

			if(nowEnemyRect.intersectsRect(nowBulletRect)&&!(nowEnemyRect.intersectsRect(m_ship->shipRect())))  //any bullets collide any enemy
			{    
				//load effect
		        Effect* effect=Effect::create();
				effect->explode(this,nowEnemy->getPosition());
				m_allEnemyArray->removeObject(nowEnemy);
				nowEnemy->removeFromParent();
				m_allPlayerBulletArray->removeObject(nowBullet);
				nowBullet->removeFromParent();
				Config::sharedConfig()->setScore(100);
			}
			
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
void HelloWorld::updateUI(float dt)
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
		this->shipIcon3->setVisible(false);
		break;
	case 1:
		this->shipIcon2->setVisible(false);
		break;
	case 0:
		this->shipIcon1->setVisible(false);
		break;
	}
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
	mIsTouching=true;

	return true;
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch *pTouch,cocos2d::CCEvent *pEvent)
{
	if(mIsTouching){
		CCPoint touchPos=CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
		CCPoint moveDelta=ccpSub(touchPos,mTouchPos);
		CCPoint nextPos=ccpAdd(m_ship->getChildByTag(747)->getPosition(),moveDelta);

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
