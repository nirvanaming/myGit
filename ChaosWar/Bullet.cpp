//
//Bullet.cpp
//
//created by Tim on Oct 25th 2013
//
#include "Bullet.h"
#include "Config.h"


Bullet::Bullet(void)
{
	_moveSpeed=1;
	_HP=1;
	_active=true;
	_damage=1;
}


Bullet::~Bullet(void)
{
}



bool Bullet::initWithFile(const char* weapon,float speed,int damage)
{
	bool bRet=false;
	do
	{
		_moveSpeed=speed;
		_HP=1;
		_active=true;
		_damage=damage;

		scheduleUpdate();
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bullet.plist");
		this->initWithSpriteFrameName(weapon);
		ccBlendFunc cb1={GL_SRC_ALPHA,GL_ONE};
		this->setBlendFunc(cb1);

		bRet=true;
	}while(0);
	return bRet;
}


Bullet* Bullet::create(const char* weapon,float speed,int damage)
{
	Bullet* pRet=new Bullet;
	if(pRet && pRet->initWithFile(weapon,speed,damage))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}



void Bullet::update(float dt)
{
	if(this->_HP<=0)
	{
		_active=false;
	}
}


void Bullet::hurt(float damage)
{

	_HP-=damage;
}


void Bullet::destroy()
{
	_allShipBulletArray->removeObject(this);
	this->removeFromParent();
}

CCRect Bullet::Rect()
{
	return CCRectMake(
		this->getPosition().x-(this->getContentSize().width/2),
		this->getPosition().y-(this->getContentSize().height/2),
		this->getContentSize().width/2,
		this->getContentSize().height/2 );
}


bool Bullet::isActive()
{
	return this->_active;
}



int Bullet::getDamage()
{
	return _damage;

}