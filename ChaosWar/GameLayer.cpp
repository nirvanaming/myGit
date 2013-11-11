#include "GameLayer.h"
//#include "HRocker.h"
#include "Defines.h"
#include "Config.h"
#include "Enemys.h"
#include "Effects.h"
#include "GameOver.h"




GameLayer::GameLayer(void)
{
	_tileMap=NULL;
	_hud=NULL;
	_enemyManage=NULL;
	_MapRect=CCRectMake(0,0,MAPWIDTH,MAPHEIGHT);
	_motionStreak=NULL;
}


GameLayer::~GameLayer(void)
{
	if(_enemyManage)
	{
		delete _enemyManage;
		_enemyManage=NULL;
	}
	_allEnemyArray->release();
	_allEnemyArray=NULL;
	/*_allEnemyBulletArray->release();
	_allEnemyBulletArray=NULL;*/
	_allShipBulletArray->release();
	_allShipBulletArray=NULL;

	this->unscheduleUpdate();
}

bool GameLayer::init()
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());

		this->initArray();
		this->initBg();
		this->initHero();
		//this->initEnemy();
		this->initMotionStreak();
		if(Hero::sharedHero()->isActive())
		{
		this->scheduleUpdate();
		}
		//schedule(schedule_selector(GameLayer::loadEnemy), 1.0f);


		bRet=true;
	}while(0);
	return bRet;
}

void GameLayer::initBg()
{
	CCSprite* lastBG=CCSprite::create("HelloWorld.png");
	CCAssert(lastBG!=NULL, "HelloWorld.png not found");
	lastBG->setScale(2.2f);
	lastBG->setAnchorPoint(ccp(0,0));

	_tileMap=CCTMXTiledMap::create("TileMap.tmx");
	CCAssert(_tileMap!=NULL, "TileMap.tmx not found");
	_tileMap->setAnchorPoint(ccp(0,0));

	CCSprite* firstBG=CCSprite::create("CloseNormal.png");
	CCAssert(firstBG!=NULL,"CloseNormal.png not found");
	firstBG->setScale(25.0f);
	firstBG->setAnchorPoint(ccp(0,0));

	CCParallaxNode* voidNode = CCParallaxNode::create();
	// background image is moved at a ratio of 0.4x, 0.5y
	voidNode->addChild(lastBG, -1, ccp(0.4f,0.5f), CCPointZero);
    
    // tiles are moved at a ratio of 1.0, 1.0y
    voidNode->addChild(_tileMap, 1, ccp(1.0f,1.0f), ccp(0,-200) );
    
    // top image is moved at a ratio of 3.0x, 2.5y
	voidNode->addChild( firstBG, 2, ccp(3.0f,2.5f), ccp(200,1000) );
    addChild(voidNode, 0, 123);
	

	/*_tileMap=CCTMXTiledMap::create("TileMap.tmx");
	CCObject* pObject=NULL;
	CCARRAY_FOREACH(_tileMap->getChildren(),pObject)
	{
		CCTMXLayer* child=(CCTMXLayer*)pObject;
		child->getTexture()->setAliasTexParameters();
	}
	this->addChild(_tileMap,-6);*/
}

void GameLayer::initArray()
{
	_allEnemyArray=CCArray::create();
	_allEnemyArray->retain();

	//_allEnemyBulletArray=CCArray::create();
	//_allEnemyBulletArray->retain();

	_allShipBulletArray=CCArray::create();
	_allShipBulletArray->retain();

}

void GameLayer::initHero()
{
	
	CCSize size=CCDirector::sharedDirector()->getWinSize();
	//Hero::sharedHero()=Hero::create("HexPilot.png",HEROMAXLIFE,HEROSPEEED);
	//this->addChild(Hero::sharedHero(),100,999);
	this->addChild(Hero::sharedHero(),100,999);

	CCTMXObjectGroup *objects = _tileMap->objectGroupNamed("Hero");
    CCAssert(objects != NULL, "Objects' object group not found");
	CCDictionary *spawnPoint = objects->objectNamed("SpawnPoint");
	CCAssert(spawnPoint != NULL, "SpawnPoint object not found");
	int x = spawnPoint->valueForKey("x")->intValue();
	int y = spawnPoint->valueForKey("y")->intValue();
	//Hero::sharedHero()->setPosition(ccp(x,y));
	Hero::sharedHero()->setPosition(ccp(x,y));

	//this->setViewpointCenter(Hero::sharedHero()->getPosition());
	this->setViewpointCenter(Hero::sharedHero()->getPosition());
}


void GameLayer::initEnemy()
{
	Enemys::sharedEnemys();
	Effects::sharedExplosion();
	_enemyManage=new EnemyManage(this);
}


void GameLayer::initMotionStreak()
{
	_motionStreak=CCMotionStreak::create(0.5,1,30,ccc3(0,255,255),"streak.png");
	CCAssert(_motionStreak!=NULL, "streak.png not found");
	addChild(_motionStreak);
}


void GameLayer::setViewpointCenter(CCPoint position)
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int x=MAX(position.x,winSize.width/2);
	int y=MAX(position.y,winSize.height/2);
	x=MIN(x,(_tileMap->getMapSize().width*_tileMap->getTileSize().width)-winSize.width/2);
	y=MIN(y,(_tileMap->getMapSize().height*_tileMap->getTileSize().height)-winSize.height/2);
	CCPoint actualPosition=ccp(x,y);

	CCPoint centerofView=ccp(winSize.width/2,winSize.height/2);
	CCPoint viewPoint=ccpSub(centerofView,actualPosition);
	this->setPosition(viewPoint);

	/*this->runAction(CCFollow::create(Hero::sharedHero()));*/
}



//L dpad
void GameLayer::didChangeDirectionTo(DPad* dPad,CCPoint direction,float acce)
{
		//Hero::sharedHero()->moveWithDirection(direction,acce);
	Hero::sharedHero()->moveWithDirection(direction,acce);
}

void GameLayer::isHoldingDirection(DPad* dPad,CCPoint direction,float acce)
{
		//Hero::sharedHero()->moveWithDirection(direction,acce);	
	Hero::sharedHero()->moveWithDirection(direction,acce);
}

void GameLayer::simpleDPadTouchEnded(DPad* dPad)
{
		Hero::sharedHero()->stopMove();   //end move
}


//R dpad
void GameLayer::didChangeRotationTo(RightDPad* RDpad,float degree,CCPoint direction)
{
	Hero::sharedHero()->setRotationWithDegree(degree);
	//shoot bullet
		Hero::sharedHero()->setShoot(true);
	   Hero::sharedHero()->shootTowardWithDirection(direction);
}

void GameLayer::isHoldingRotation(RightDPad* RDpad,float degree, CCPoint direction)
{

	Hero::sharedHero()->setRotationWithDegree(degree);
	//shoot bullet
		Hero::sharedHero()->setShoot(true);
	   Hero::sharedHero()->shootTowardWithDirection(direction);
}

void GameLayer::RightDPadTouchEnded(RightDPad* RDpad)
{
	Hero::sharedHero()->stopShoot();   //end shoot
}


void GameLayer::update(float dt)
{
	

	Hero::sharedHero()->update(dt);
	this->updatePositions();
	this->setViewpointCenter(Hero::sharedHero()->getPosition());
	this->updateRotation();
	_motionStreak->setPosition(Hero::sharedHero()->getPosition());
	this->isCollide();
	this->removeInactiveUnit(dt);

	this->updateFollowEnemy();
	this->updateRandomMoveEnemy();
	this->checkIsGo();

}



void GameLayer::updatePositions()
{
	if(Hero::sharedHero()->isActive())
	{
	float posX = MIN(_tileMap->getMapSize().width * _tileMap->getTileSize().width - Hero::sharedHero()->getCenterToSides(),
		MAX(Hero::sharedHero()->getCenterToSides(), Hero::sharedHero()->getDesirePosition().x));
	float posY = MIN(_tileMap->getMapSize().height * _tileMap->getTileSize().height-Hero::sharedHero()->getCenterToBottom(),
        MAX(Hero::sharedHero()->getCenterToBottom(), Hero::sharedHero()->getDesirePosition().y));
    Hero::sharedHero()->setPosition(ccp(posX, posY));
	}
}


void GameLayer::updateRotation()
{
	if(Hero::sharedHero()->isActive())
	{
	float actualDegree=Hero::sharedHero()->getDesireDegree();
	Hero::sharedHero()->setRotation(actualDegree);
	}
	
}





void GameLayer::loadEnemy(float dt)
{
	_time++;
	_enemyManage->loadResource(_time);
}



bool GameLayer::collide(Unit* a, Unit* b)
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


void GameLayer::isCollide()
{
	CCObject* enemys=NULL;
	CCObject* heroBullets=NULL;
	CCArray* _enemyToBeDeleted=CCArray::create();
	CCArray* _heroBulletsToBeDeleted=CCArray::create();

	CCARRAY_FOREACH(_allEnemyArray,enemys)
	{
		Unit* enemy=dynamic_cast<Unit*>(enemys);
		Unit* ship=dynamic_cast<Unit*>(Hero::sharedHero());

		CCARRAY_FOREACH(_allShipBulletArray,heroBullets)
		{
			Unit* heroBullet=dynamic_cast<Unit*>(heroBullets);
			if(this->collide(enemy,heroBullet))
			{
				enemy->hurt(heroBullet->getDamage());
				heroBullet->hurt(1);
			}
			if(!(_MapRect.intersectsRect(heroBullet->boundingBox())))
			{
				/*_allShipBulletArray->removeObject(heroBullet);*/
				heroBullet->removeFromParent();
				_heroBulletsToBeDeleted->addObject(heroBullet);
				
			}

		}
		if(collide(enemy,Hero::sharedHero()))
		{
			if(Hero::sharedHero()->isActive())
			{
				enemy->hurt(1);
				Hero::sharedHero()->hurt(1);
				CCLog("%d",Hero::sharedHero()->getHP());
			}
	    }
		if(!(_MapRect.intersectsRect(enemy->boundingBox())))
		{
			/*_allEnemyArray->removeObject(enemy);*/
			enemy->removeFromParent();
			_enemyToBeDeleted->addObject(enemy);
		}
	}

	CCARRAY_FOREACH(_heroBulletsToBeDeleted,heroBullets)
	{
		_allShipBulletArray->removeObject(heroBullets);
	}
	_heroBulletsToBeDeleted->removeAllObjects();

	CCARRAY_FOREACH(_enemyToBeDeleted,enemys)
	{
		_allEnemyArray->removeObject(enemys);
	}
	_enemyToBeDeleted->removeAllObjects();

	//below can add enemy bullets
}



void GameLayer::removeInactiveUnit(float dt)
{
	CCArray* children=this->getChildren();
	for(unsigned int i=0; i<children->count();i++)
	{
		CCSprite* child=dynamic_cast<CCSprite*>(children->objectAtIndex(i));
		if(child)
		{
			child->update(dt);
			int tag=child->getTag();
			if(tag==777||tag==888)   //shipbullet:777, enemy:888, ship:999,enemybullet:666
			{
				if(!((Unit*)child)->isActive())
			   {
				((Unit*)child)->destroy();
			   }
			}

        }
	}
	if(Hero::sharedHero())
	{
		if(!Hero::sharedHero()->isActive())
		{
			Hero::sharedHero()->destroy();
			//Hero::sharedHero()=NULL;
		}	
	}

}



void GameLayer::updateFollowEnemy()
{
	for(unsigned int i=0;i<_allEnemyArray->count();++i)
	{

		Enemys* followEnemy=(Enemys*)_allEnemyArray->objectAtIndex(i);
		if(followEnemy->getMoveType()==1)
		{
			///*CCMoveBy* moveB=CCMoveBy::create(100,
			//	ccp(Hero::sharedHero()->getPosition().x-followEnemy->getPosition().x,
			//	Hero::sharedHero()->getPosition().y-followEnemy->getPosition().y));*/
			//CCDelayTime* delayT=CCDelayTime::create(0.5);
			//CCMoveTo* moveT=CCMoveTo::create(5,Hero::sharedHero()->getPosition());
			//CCSequence* seq=CCSequence::create(delayT,moveT,NULL);
			//followEnemy->runAction(seq);

			followEnemy->trackMove(Hero::sharedHero());
		}

	}

}



void GameLayer::updateRandomMoveEnemy()
{
	for(unsigned int i=0;i<_allEnemyArray->count();++i)
	{

		Enemys* followEnemy=(Enemys*)_allEnemyArray->objectAtIndex(i);
		if(followEnemy->getMoveType()==3)
		{
			CCMoveBy* moveB=CCMoveBy::create(130,
				ccp(Hero::sharedHero()->getPosition().x-followEnemy->getPosition().x,
				Hero::sharedHero()->getPosition().y-followEnemy->getPosition().y));
			CCDelayTime* delayT=CCDelayTime::create(0.5);
			CCSequence* seq=CCSequence::create(delayT,moveB,NULL);
			followEnemy->runAction(seq);
		}
	}
}



void GameLayer::checkIsGo()
{
	if(!Hero::sharedHero()->isActive())
	{
		//this->stopAllActions();
		/*CCCallFuncN* GO=CCCallFuncN::create(this,callfuncN_selector(GameLayer::goCallBack));
		this->runAction(CCSequence::create(CCDelayTime::create(3.0f),GO,NULL));*/
		this->goCallBack();
	}
}



void GameLayer::goCallBack()
{
	CCScene* gameOverScene=GameOver::createScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, gameOverScene));
}