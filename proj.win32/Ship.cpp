//
//Ship.cpp
//
//created by Tim on Aug 16th 2013
//

#include "Ship.h"
#include "Bullet.h"

using namespace cocos2d;

Ship::Ship():m_bulletSpeed(800),m_appearPosition(CCPointZero)
{

}

Ship::~Ship()
{

}

bool Ship::init()
{
	if(!CCSprite::init())
	{
		return false;
	}

	CCSprite* ship=CCSprite::create("Download/SkyWard.png", CCRectMake(0,0,100,60));
	this->addChild(ship);
	this->setPosition(m_appearPosition);

	//�ӵ�����
	this->schedule(schedule_selector(Ship::shoot),0.16f);

	return true;
}


void Ship::update(float dt)
{
}


void Ship::shoot(float dt)
{
	//����һ���ӵ�����ӵ�BatchNode�С�  
	Bullet* bullet_a=Bullet::create();
	CCSprite* newBullet = CCSprite::createWithTexture(bullet_a->m_bulletSprite->getTexture());  
    newBullet->setPosition(CCPointZero);  
    bullet_a->m_bulletSprite->addChild(newBullet);  
      
    //����ӵ����Ѵ����ӵ�����  
    bullet_a->m_allBulletArray->addObject(newBullet);  
}

void Ship::destroy()
{
	CCLOG("destroy one ship");
	this->removeFromParent();
}

CCRect Ship::shipRect()
{
	CCPoint pos=getPosition();
	CCSize cs=getContentSize();

	return CCRectMake(pos.x-cs.width/2,pos.y-cs.height/2,
		cs.width,cs.height/2);
}


