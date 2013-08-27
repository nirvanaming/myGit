//
//Bullet.cpp
//
//created by Tim on Aug 14th, 2013
//

#include "Bullet.h"
#include "Ship.h"


Bullet::Bullet(){}

Bullet::~Bullet()
{

}




bool Bullet::init()
{
	bool sRet=false;
	do{
		CC_BREAK_IF(!CCLayer::init());
		//��ʼ���ӵ�����
		this->m_allBulletArray=CCArray::create();
		m_allBulletArray->retain();
		this->m_bulletSprite=CCSpriteBatchNode::create("Download/HexBullet2.png");
		this->addChild(m_bulletSprite);
		//ÿ��300�������1�ӵ�
		this->schedule(schedule_selector(Bullet::addNewBullet),0.3f);
		//ÿ��100�����ƶ��ӵ�
		this->schedule(schedule_selector(Bullet::moveBullet),0.01f);
		sRet=true;

	}while(0);

	return sRet;
}

void Bullet::addNewBullet(float dt)  //����ӵ�
{
	CCSprite* spriteBullet=CCSprite::createWithTexture(this->m_bulletSprite->getTexture());
	this->m_bulletSprite->addChild(spriteBullet);
	CCPoint pos=Ship::sharedShip->getChildByTag(747)->getPosition();
	CCPoint startPos=ccp(pos.x+spriteBullet->getContentSize().width/2,pos.y); //�ӵ�������Ϊ��ͼ�ҷ�
	spriteBullet->setPosition(startPos);
	this->m_allBulletArray->addObject(spriteBullet);
}


void Bullet::moveBullet(float dt)   //�ӵ��ƶ�
{
	for(unsigned int i=0;i<m_allBulletArray->count();i++)
	{
		CCSprite* nowBullet=(CCSprite*)m_allBulletArray->objectAtIndex(i);
		nowBullet->setPositionX(nowBullet->getPositionX()+50);
		if(nowBullet->getPositionX()>=480)
		{
			m_allBulletArray->removeObjectAtIndex(i);
			m_bulletSprite->removeChild(nowBullet,true);
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
