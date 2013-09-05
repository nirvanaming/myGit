//
//Enemy.cpp
//
//created by Tim on Aug 21st 2013
//
#include "Enemy.h"
#include "GameOverScene.h"
#include "Effect.h"
#include "Config.h"
#include "Bullet.h"

using namespace cocos2d;

Enemy::Enemy(void)
{
}


Enemy::~Enemy(void)
{
	m_allEnemyArray->release();
}

bool Enemy::init()
{
	bool sRet=false;
	do{
		CC_BREAK_IF(!CCLayer::init());
		//init the enemy array
		m_allEnemyArray=CCArray::create();
		m_allEnemyArray->retain();
		m_allEnemyBulletArray=CCArray::create();
		m_allEnemyBulletArray->retain();

		//this->m_enemySprite=CCSpriteBatchNode::create("Download/HexPilot.png");
		this->m_enemySprite=CCSpriteBatchNode::create("Download/HexPilot.png");
		this->addChild(m_enemySprite);

		//apply schedule call back
		//add an enemy every dt
		this->schedule(schedule_selector(Enemy::addEnemy),0.7f);
		//move enemy every dt
		//this->schedule(schedule_selector(Enemy::moveEnemy),0.5f);
		//this->schedule(schedule_selector(Enemy::moveLogic),3.0f);

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

	///////////////////////////////////////////////////////////move enemy
	    CCPoint pos=spriteEnemy->getPosition();
		int endY=CCRANDOM_0_1()*320;
		int type = CCRANDOM_0_1()*2;  //get [0,1]
		int duration=CCRANDOM_0_1()*2+2;
		ccBezierConfig bezier2;
		bezier2.controlPoint_1 = CCPointMake(pos.x ,pos.y+200);
		bezier2.controlPoint_2 = CCPointMake(pos.x -300,pos.y-200);
		bezier2.endPosition = CCPointMake(0,pos.y);
		CCBezierTo * bezierBy2 = CCBezierTo::create(duration, bezier2);
        ccBezierConfig bezier1;
		bezier1.controlPoint_1 = CCPointMake(pos.x + 200,pos.y-150);
		bezier1.controlPoint_2 = CCPointMake(pos.x - 200,pos.y+200);
		bezier1.endPosition = CCPointMake(0,endY);
		CCBezierTo * bezierBy1 = CCBezierTo::create(duration, bezier1);

		CCFiniteTimeAction* actionMoveDone=CCCallFuncN::create(
		this,callfuncN_selector(Enemy::spriteMoveFinished));

		switch(type){

		case 0:
		spriteEnemy->runAction(
			CCSequence::create(bezierBy2,actionMoveDone,NULL));
			break;
		case 1:
		spriteEnemy->runAction(
			CCSequence::create(bezierBy1,actionMoveDone,NULL));
			break;
		}
		

/////////////////////////////////////////////////////////


	    m_allEnemyArray->addObject(spriteEnemy);

}

/*
void Enemy::moveEnemy()
{

	for(unsigned int i=0;i<m_allEnemyArray->count();i++)
	{

		CCSprite* nowEnemy=(CCSprite*)m_allEnemyArray->objectAtIndex(i);
		
        //int randomX=CCRANDOM_0_1()*3+5.4;
		//int randomY=CCRANDOM_0_1()*320;
		//int randomD=CCRANDOM_0_1()*2+3;
		//nowEnemy->setPositionX(nowEnemy->getPosition().x-randomX);
		//nowEnemy->runAction(CCMoveTo::create(randomD,ccp(0-nowEnemy->getContentSize().width,randomY)));
		
		CCPoint pos=nowEnemy->getPosition();
		int type = CCRANDOM_0_1() * 4;
		ccBezierConfig bezier2;
		bezier2.controlPoint_1 = CCPointMake(pos.x +100,0);
		bezier2.controlPoint_2 = CCPointMake(pos.x -200,pos.y+100);
		bezier2.endPosition = CCPointMake(0,pos.y);
        CCBezierTo * bezierBy2 = CCBezierTo::create(2.0f, bezier2);
        ccBezierConfig bezier1;
		bezier1.controlPoint_1 = CCPointMake(pos.x + 400,330);
		bezier1.controlPoint_2 = CCPointMake(pos.x - 400,280);
		bezier1.endPosition = CCPointMake(pos.x,-70);
        CCBezierTo * bezierBy1 = CCBezierTo::create(3.0f, bezier1);

		nowEnemy->runAction(bezierBy2);

		if(nowEnemy->getPosition().x<=2)
		{
			m_allEnemyArray->removeObjectAtIndex(i);
			m_enemySprite->removeChild(nowEnemy,true);
			GameOverScene* gameoverscene=GameOverScene::create();
			char score[20];
			sprintf(score,"%06d",Config::sharedConfig()->getScore());
			gameoverscene->getlayer()->getlabel()->setString(score);
			CCDirector::sharedDirector()->replaceScene(gameoverscene);
		}
	}
}
*/

   
void Enemy::spriteMoveFinished(CCNode* sender)
{
	//this->removeFromParent();
	CCSprite *sprite=(CCSprite*) sender;
	//this->removeChild(sprite,true);
	m_allEnemyArray->removeObject(sprite);
	m_enemySprite->removeChild(sprite,true);

}



