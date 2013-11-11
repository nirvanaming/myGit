//
//BigBullet.cpp
//
//created by Tim on Sep 13rd
//

#include "BigBullet.h"
#include "Config.h"
#include "Effect.h"


BigBullet::BigBullet(void)
{
	moveSpeed=100;
	m_HP=1;
}


BigBullet::~BigBullet(void)
{
	
}

bool BigBullet::initWithFile(const char* weapon, int speed)
{
	
	bool sRect=false;

	do{
		CC_BREAK_IF(!Unit::init());
		
		moveSpeed=speed;
		m_HP=1;
		m_active=true;
		scheduleUpdate();
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bullet.plist");
		this->initWithSpriteFrameName(weapon);
		ccBlendFunc cb1={GL_SRC_ALPHA,GL_ONE};
		this->setBlendFunc(cb1);
		sRect=true;
	}while(0);

	return sRect;
}




BigBullet* BigBullet::create(const char* weapon,int speed)
{
	BigBullet* pBigBullet=new BigBullet();
	if(pBigBullet && pBigBullet->initWithFile(weapon, speed))
	{
		pBigBullet->autorelease();
		return pBigBullet;
	}else{

		delete pBigBullet;
		pBigBullet=NULL;
		return NULL;
	}

}



void BigBullet::update(float dt)
{
	
	CCPoint position=this->getPosition();
	if(moveSpeed>0){
	position.x+=this->moveSpeed*dt;
	}
	else
		position.x-=-(this->moveSpeed)*dt;
	this->setPosition(ccp(position.x,position.y));
	
	if(this->m_HP<=0)
	{
		this->m_active=false;
	}
}

CCRect BigBullet::Rect()
{
	return CCRectMake(
		this->getPosition().x-(this->getContentSize().width/2),
		this->getPosition().y-(this->getContentSize().height/2),
		this->getContentSize().width/2,
		this->getContentSize().height/2 );
}


void BigBullet::hurt()
{
	 m_HP--;
}


void BigBullet::destroy()
{
	Effect* hitEffect=Effect::create();
	hitEffect->hit(getParent(),this->getPosition());

	m_allBigBulletArray->removeObject(this);
	m_allEnemyBulletArray->removeObject(this);
	this->removeFromParent();

}


bool BigBullet::isActive()
{
	return this->m_active;
}
