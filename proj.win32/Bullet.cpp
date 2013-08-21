//
//Bullet.cpp
//
//created by Tim on Aug 14th, 2013
//

#include "Bullet.h"

Bullet::Bullet():
	m_velocityx(200),
	m_velocityy(0){}

Bullet::~Bullet()
{
m_allBulletArray->release();  
}




bool Bullet::init()
{
	if(!CCSprite::init())
	{
		return false;
	}
	initData();
	return true;
}

void Bullet::initData()
{
	winSize = CCDirector::sharedDirector()->getWinSize();  
      
    //�����������飬�����Ѵ��ڵ��ӵ�  
    m_allBulletArray = CCArray::create();  
    m_allBulletArray->retain();  
      
    //�ӵ���ͼ  
    m_bulletSprite = CCSpriteBatchNode::create("Download/HexBullet2.png");  
    m_bulletSprite->setPosition(CCPointZero);  
    addChild(m_bulletSprite);  
      
    //�����ӵ��ٶ�  
	schedule(schedule_selector(Bullet::update));  

}


void Bullet::update(float dt)
{
	CCPoint position=this->getPosition();
	position.x-=m_velocityx*dt;
	position.y-=m_velocityy*dt;
	setPosition(position);
}

CCRect Bullet::bulletRect()
{
	CCPoint pos=this->getPosition();
	return CCRectMake(pos.x-3,pos.y-3,6,6);
}




