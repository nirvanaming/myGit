//
//Enemy.cpp
//
//created by Tim on Aug 21st 2013
//
#include <string>
#include "Enemy.h"
#include "Effect.h"
#include "Config.h"
#include "BigBullet.h"

using namespace cocos2d;

Enemy::Enemy(void):
	m_active(true)
	,m_speed(200)
	,m_bulletSpeed(-200)
	,m_HP(15)
	,m_moveType(0)
	,m_scoreValue(200)
	,m_delayTime(0.8+1.2*CCRANDOM_0_1())
{

}


Enemy::~Enemy(void)
{

}


bool Enemy::initWithFile(EnemyType type)
{
	bool sRet=false;
	do{
		CC_BREAK_IF(!Unit::init());
		m_HP=type.hp;
		m_moveType=type.moveType;
		m_scoreValue=type.scoreValue;

		this->initWithSpriteFrameName(type.textureName.c_str());
		this->schedule(schedule_selector(Enemy::shoot),this->m_delayTime);
   
    sRet=true;
	}while(0);

	return sRet;
}


Enemy* Enemy::create(EnemyType type)
{
	Enemy* enemy=new Enemy();
	if(enemy&&enemy->initWithFile(type))
	{
		enemy->autorelease();
		return enemy;
	}else{
		delete enemy;
		enemy=NULL;
		return NULL;
         }
}




void Enemy::update(float dt)
{
	if(m_HP<=0)
		{
			this->m_active=false;
		}

}



void Enemy::hurt()
{
   m_HP--;
 
}


void Enemy::destroy()
{
	Config::sharedConfig()->setScore(m_scoreValue);
	Effect* effect=Effect::create();
	effect->explode(this->getParent(),this->getPosition());
	m_allEnemyArray->removeObject(this);
	this->removeFromParent();
}

CCRect Enemy::Rect()
{
	return CCRectMake(
		this->getPosition().x-(this->getContentSize().width/2),
		this->getPosition().y-(this->getContentSize().height/2),
		this->getContentSize().width/2,
		this->getContentSize().height/2 );
}

bool Enemy::isActive()
{
	return m_active;
}

void Enemy::shoot(float dt)
{
	CCPoint position=this->getPosition();
	BigBullet* bigBullet=BigBullet::create("W2.png",m_bulletSpeed);   // in plist 2 kind of texture are W1.png and W2.png
	if(bigBullet){
		m_allEnemyBulletArray->addObject(bigBullet);
		getParent()->addChild(bigBullet,1000,666);
		bigBullet->setPosition(ccp(position.x-10,position.y));
	}else{
		delete bigBullet;
		bigBullet=0;
	}

}

void Enemy::sharedEnemy()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Enemy.plist","Enemy.png");
}

int Enemy::getMoveType()
{

	return m_moveType;
}