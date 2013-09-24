//
//EnemyActionMag.cpp
//
//created by tim on Spet 23rd
//
#include "Enemy.h"
#include "EnemyActionMag.h"
#include "HelloWorldScene.h"


EnemyActionMag::EnemyActionMag(CCLayer* gameLayer)
{
	m_gameLayer=gameLayer;
	m_enemies=Config::sharedConfig()->getEnemies();
	m_enemyType=Config::sharedConfig()->getEnemyType();
}


EnemyActionMag::~EnemyActionMag()
{
}


void EnemyActionMag::loadResource(int dt)
{
	for(vector<EnemyInfo>::iterator iter=m_enemies.begin();iter!=m_enemies.end();++iter)
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

void EnemyActionMag::addEnemyToGameLayer(int type)
{
	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	EnemyType enemyType=m_enemyType[type];
	Enemy* enemy=Enemy::create(enemyType);

	CCPoint enemyPos = ccp( winSize.width,80+(winSize.height-160)*CCRANDOM_0_1());
    CCSize eSize = enemy->getContentSize();
    enemy->setPosition(enemyPos);

	CCPoint offset;
	CCAction* tempAction;
	CCMoveBy* a0;
	CCMoveBy* a1;
	CCCallFuncN* complete;

	switch(enemy->getMoveType())
	{
	case 0:
		if(((HelloWorld*)m_gameLayer)->getShip())
		{
			offset=((HelloWorld*)m_gameLayer)->getShip()->getPosition();
		}else{
			offset=ccp(-100, winSize.height/2);
		}
		tempAction=CCMoveTo::create(1,offset);
		break;

	case 1:
		offset = ccp(-winSize.width - eSize.width,0 );
        tempAction = CCMoveBy::create(4, offset);
        break;

	case 2:
		offset=ccp(-200-200*CCRANDOM_0_1(),100);
		a0=CCMoveBy::create(1.5,offset);
		a1=CCMoveBy::create(1,ccp(-160,160+50*CCRANDOM_0_1()));

		complete=CCCallFuncN::create(enemy,callfuncN_selector(EnemyActionMag::repeatAction));
		tempAction=CCSequence::create(a0,a1,complete,NULL);
		break;

	case 3:
		int newY=(enemyPos.y>=winSize.height/2)?320:-320;
		a0=CCMoveBy::create(4,ccp(-240,newY));
		a1=CCMoveBy::create(4,ccp(-320,-newY));
		tempAction=CCSequence::create(a0,a1,NULL);
		break;

}
	enemy->setRotation(90);
	m_gameLayer->addChild(enemy,1000,888);
	m_allEnemyArray->addObject(enemy);
	enemy->runAction(tempAction);
}


void EnemyActionMag::repeatAction(CCNode* pSender)
{
	CCDelayTime *delay =  CCDelayTime::create(1);
    //CCMoveBy *mv = CCMoveBy::create(1, ccp(100 + 100 * CCRANDOM_0_1(), 0));
	CCMoveBy *mv = CCMoveBy::create(1, ccp(-160, 220-100*CCRANDOM_0_1()));
    CCFiniteTimeAction *seq = CCSequence::create(delay, mv, delay->copy(), mv->reverse(), NULL);
    pSender->runAction(CCRepeatForever::create((CCActionInterval*)seq));

}