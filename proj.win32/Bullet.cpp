//
//Bullet.cpp
//
//created by Tim on Aug 14th, 2013
//

#include "Bullet.h"
#include "Ship.h"
#include "Config.h"


Bullet::Bullet(){}

Bullet::~Bullet()
{

}




bool Bullet::init()
{
	
	bool sRet=false;
	do{
		CC_BREAK_IF(!CCLayer::init());
		//init bullets array
		m_allPlayerBulletArray=CCArray::create();
		m_allPlayerBulletArray->retain();
		m_allEnemyBulletArray=CCArray::create();
		m_allEnemyBulletArray->retain();
		this->m_bulletSprite=CCSpriteBatchNode::create("Download/HexBullet2.png");
		this->addChild(m_bulletSprite);
		this->m_enemyBulletSprite=CCSpriteBatchNode::create("Download/HexBullet.png");
	    this->addChild(m_enemyBulletSprite);

		//add 1 bullet every dt
		this->schedule(schedule_selector(Bullet::addNewShipBullet),0.3f);
		//move bullet every dt
		this->schedule(schedule_selector(Bullet::moveShipBullet),0.01f);
		this->schedule(schedule_selector(Bullet::addNewEnemyBullet),0.6f);
		this->schedule(schedule_selector(Bullet::moveEnemyBullet),0.01f);
		sRet=true;

	}while(0);

	return sRet;
	
    return true;
}


void Bullet::addNewShipBullet(float dt)  //add new bullet
{
	CCSprite* spriteBullet1=CCSprite::createWithTexture(this->m_bulletSprite->getTexture());
	CCSprite* spriteBullet2=CCSprite::createWithTexture(this->m_bulletSprite->getTexture());
	this->m_bulletSprite->addChild(spriteBullet1);
	this->m_bulletSprite->addChild(spriteBullet2);
	CCPoint pos=Ship::sharedShip->getChildByTag(747)->getPosition();
	CCPoint startPos1=ccp(pos.x-5,pos.y-10); //bullets start point is right of ship rect
	CCPoint startPos2=ccp(pos.x-5,pos.y+10);
	spriteBullet1->setPosition(startPos1);
	spriteBullet2->setPosition(startPos2);
	m_allPlayerBulletArray->addObject(spriteBullet1);
	m_allPlayerBulletArray->addObject(spriteBullet2);
}


void Bullet::addNewEnemyBullet(float dt)
{
	
	CCSprite* e_spriteBullet=CCSprite::createWithTexture(this->m_enemyBulletSprite->getTexture());
	e_spriteBullet->setRotation(180);
	this->m_enemyBulletSprite->addChild(e_spriteBullet);
	for(unsigned int i=0;i<m_allEnemyArray->count();i++)
	{
	
		CCSprite* nowEnemy=(CCSprite*)m_allEnemyArray->objectAtIndex(i);
		CCPoint pos=nowEnemy->getPosition();
		CCPoint startPos=ccp(pos.x-20,pos.y);
		e_spriteBullet->setPosition(pos);
	}
	
		m_allEnemyBulletArray->addObject(e_spriteBullet);
		
}



void Bullet::moveShipBullet(float dt)   //move bullet
{
	for(unsigned int i=0;i<m_allPlayerBulletArray->count();i++)
	{
		CCSprite* nowBullet=(CCSprite*)m_allPlayerBulletArray->objectAtIndex(i);
		nowBullet->setPositionX(nowBullet->getPositionX()+50);      //move 50 pixels every dt 
		if(nowBullet->getPositionX()>=480)
		{
			m_allPlayerBulletArray->removeObjectAtIndex(i);
			m_bulletSprite->removeChild(nowBullet,true);
		}
	}

}

void Bullet::moveEnemyBullet(float dt)   //move enemy bullet
{
	for(unsigned int i=0;i<m_allEnemyBulletArray->count();i++)
	{
		CCSprite* nowBullet2=(CCSprite*)m_allEnemyBulletArray->objectAtIndex(i);
		nowBullet2->setPositionX(nowBullet2->getPositionX()-5);
		if(nowBullet2->getPositionX()<=10)
		{
			m_allEnemyBulletArray->removeObjectAtIndex(i);
			m_enemyBulletSprite->removeChild(nowBullet2,true);
		}
	}
}





/*
CCRect Bullet::bulletRect()
{
	for(unsigned int i=0;i<m_allBulletArray->count();i++)
	{
		CCSprite* nowBullet=(CCSprite*)m_allBulletArray->objectAtIndex(i);

		return CCRectMake(
		           	nowBullet->getPosition().x-(nowBullet->getContentSize().width/2),
		           	nowBullet->getPosition().y-(nowBullet->getContentSize().height/2),
			        nowBullet->getContentSize().width,
		          	nowBullet->getContentSize().height);
	}
}
*/
