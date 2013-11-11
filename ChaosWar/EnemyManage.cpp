//
//EnemyManage.cpp
//
//created bt Tim on Oct 28th 2013
//
#include "EnemyManage.h"
#include "Enemys.h"
#include "GameLayer.h"
#include "Defines.h"


EnemyManage::EnemyManage(CCLayer* gameLayer)
{
	_gameLayer=gameLayer;
	_enemies=Config::sharedConfig()->getEnemies();
	_enemyType=Config::sharedConfig()->getEnemyType();
}


EnemyManage::~EnemyManage()
{
	
}


void EnemyManage::loadResource(int dt)
{
	for(vector<EnemyInfo>::iterator iter=_enemies.begin();iter!=_enemies.end();++iter)
	{
		if(iter->showType=="Repeate")
		{
			if(dt%iter->showTime==0)
			{
				for(int i=0;i!=3;++i)
				{
				addEnemyToGameLayer(iter->types[i]);
				}
			}
		}
	}
}


void EnemyManage::addEnemyToGameLayer(int type)
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	EnemyType enemyType=_enemyType[type];
	enemy=Enemys::create(enemyType);

	CCPoint enemyPosRight = ccp( MAPWIDTH,20+(MAPHEIGHT-20)*CCRANDOM_0_1());
	CCPoint enemyPosTop=ccp(20+(MAPWIDTH-20)*CCRANDOM_0_1(),MAPHEIGHT);
	CCPoint enemyPosLeft=ccp(0,20+(MAPHEIGHT-20)*CCRANDOM_0_1());
	CCPoint enemyPosDown=ccp(20+(MAPWIDTH-20)*CCRANDOM_0_1(),0);
    CCSize eSize = enemy->getContentSize();

	CCPoint offset;
	CCAction* tempAction;
	CCMoveBy* a0;
	CCMoveBy* a1;
	CCCallFuncN* complete;
	int spawnPos;

	switch (enemy->getMoveType())
	{
	case 0:     //四周随意出现，直线往另一边运动
		switch (spawnPos=CCRANDOM_0_1()*4)
		{
		case 0:
			enemy->setPosition(enemyPosRight);
			offset=ccp(-MAPWIDTH-eSize.width,0);
			break;

		case 1:
			enemy->setPosition(enemyPosDown);
			offset=ccp(0,MAPHEIGHT+eSize.height);
			break;

		case 2:
			enemy->setPosition(enemyPosLeft);
			offset=ccp(MAPWIDTH+eSize.width,0);
			break;

		case 3:
			enemy->setPosition(enemyPosTop);
			offset=ccp(0,-MAPHEIGHT-eSize.height);
			break;

		default:
			break;
		}
		tempAction=CCMoveBy::create(4,offset);
		break;

	case 1:      //随意出生，跟踪_hero
		enemy->setPosition(ccp(MAPWIDTH*CCRANDOM_0_1(),MAPHEIGHT*CCRANDOM_0_1()));
		if(Hero::sharedHero())
		{
			offset=Hero::sharedHero()->getPosition();
		}
		else
		{
			offset=ccp(0,MAPHEIGHT/2);
		}
		
		tempAction=CCMoveTo::create(5,offset);
		break;

	case 2:          //随意出生，直角运动
		enemy->setPosition(ccp(MAPWIDTH*CCRANDOM_0_1(),MAPHEIGHT*CCRANDOM_0_1()));
		offset=ccp(MAPWIDTH*CCRANDOM_0_1(),MAPHEIGHT*CCRANDOM_0_1());
		a0=CCMoveBy::create(5,offset);
		a1=CCMoveBy::create(5,ccp(MAPWIDTH*CCRANDOM_0_1(),MAPHEIGHT*CCRANDOM_0_1()));
		complete=CCCallFuncN::create(enemy,callfuncN_selector(EnemyManage::repeatAction));
		tempAction=CCSequence::create(a0,a1,complete,NULL);
		break;

	case 3:       //随意书生，根据_hero运动而随意运动（moveBy）
		enemy->setPosition(ccp(MAPWIDTH*CCRANDOM_0_1(),MAPHEIGHT*CCRANDOM_0_1()));
		if(Hero::sharedHero())
		{
			offset=Hero::sharedHero()->getPosition();
		}
		else
		{
			offset=ccp(0,MAPHEIGHT/2);
		}
		
		tempAction=CCMoveTo::create(5,offset);
		break;
	}

	_gameLayer->addChild(enemy,99,888);
	_allEnemyArray->addObject(enemy);
	enemy->runAction(tempAction);
}


void EnemyManage::repeatAction(CCNode* pSender)
{
	CCDelayTime *delay =  CCDelayTime::create(1);
	CCMoveBy *mv = CCMoveBy::create(5, ccp(MAPWIDTH*CCRANDOM_0_1(),MAPHEIGHT*CCRANDOM_0_1()));
    CCFiniteTimeAction *seq = CCSequence::create(delay, mv, delay->copy(), mv->reverse(), NULL);
    pSender->runAction(CCRepeatForever::create((CCActionInterval*)seq));
}


void EnemyManage::followHero(CCNode* pSender)
{
	
}



void EnemyManage::update(float dt)
{

}
