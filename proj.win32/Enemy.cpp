//
//Enemy.cpp
//
//created by Tim on Aug 21st 2013
//
#include "Enemy.h"
#include "GameOverScene.h"
#include "Effect.h"

using namespace cocos2d;

Enemy::Enemy(void)
{
}


Enemy::~Enemy(void)
{
	this->m_allEnemyArray->release();
}

bool Enemy::init()
{
	bool sRet=false;
	do{
		CC_BREAK_IF(!CCLayer::init());
		//初始化敌人集合
		this->m_allEnemyArray=CCArray::create();
		m_allEnemyArray->retain();

		this->m_enemySprite=CCSpriteBatchNode::create("Download/HexPilot.png");
		this->addChild(m_enemySprite);

		//安排schedule回调
		//n毫秒生成一个新敌人
		this->schedule(schedule_selector(Enemy::addEnemy),1.0f);
		//每m毫秒移动敌人
		this->schedule(schedule_selector(Enemy::moveEnemy),0.001f);

    sRet=true;
	}while(0);

	return sRet;
}


void Enemy::addEnemy(float dt)
{
	CCSprite* spriteEnemy=CCSprite::createWithTexture(this->m_enemySprite->getTexture());
	this->m_enemySprite->addChild(spriteEnemy);
	spriteEnemy->setRotation(180);
	spriteEnemy->setScale(0.7f);
	

	CCSize winSize=CCDirector::sharedDirector()->getWinSize();
	int minY=spriteEnemy->getContentSize().height/2;
	int maxY=winSize.height-spriteEnemy->getContentSize().height/2;
	int rangeY=maxY-minY;
	int actualY=(rand()%rangeY)+minY;

	//create the target slightly off-screen along the right edge
	//and along a random position along the Y axis as calculated
	spriteEnemy->setPosition(ccp(winSize.width+(spriteEnemy->getContentSize().width/2),actualY));
	this->m_allEnemyArray->addObject(spriteEnemy);

}


void Enemy::moveEnemy(float dt)
{
	for(unsigned int i=0;i<m_allEnemyArray->count();i++)
	{
		CCSprite* nowEnemy=(CCSprite*)m_allEnemyArray->objectAtIndex(i);
		int random=CCRANDOM_0_1()*3+2.4;
		nowEnemy->setPositionX(nowEnemy->getPosition().x-random);
		//nowEnemy->runAction(CCMoveTo::create(random+2,ccp(0-nowEnemy->getContentSize().width/2,nowEnemy->getPosition().y)));
		if(nowEnemy->getPosition().x<=2)
		{
			m_allEnemyArray->removeObjectAtIndex(i);
			m_enemySprite->removeChild(nowEnemy,true);
			GameOverScene* gameoverscene=GameOverScene::create();
			gameoverscene->getlayer()->getlabel()->setString("YouLose :<");
			CCDirector::sharedDirector()->replaceScene(gameoverscene);
		}
	}
}





