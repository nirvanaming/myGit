//
//Hero.cpp
//
//created by Tim on Oct 21st 2013
//
#include "Hero.h"
#include "Bullet.h"
#include "Config.h"
#include "CCShake.h"

static Hero* g_hero=NULL;

Hero::Hero(void):_HP(10),
	_active(true),
	_speed(10.0f),
	_desireDegree(0.0f),
	_timeSinceLastShot(0),
	_isShooting(false),
	_bulletSpeed(500.0f)

{
}


Hero::~Hero(void)
{
}


bool Hero::initWithFile(const char* pic,int HP,float speed)
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!Unit::init());
		_HP=HP;
		_maxHP=HP;
		_speed=speed;
		CCTexture2D* pTexture=CCTextureCache::sharedTextureCache()->addImage(pic);
		CCRect rect=CCRectMake(0,0,60,60);
		this->initWithTexture(pTexture,rect);
		this->setScale(0.5);
		this->setPosition(CENTER);

		this->setCenterToBottom(15.0);
		this->setCenterToSides(15.0);
		this->scheduleUpdate();

		


		bRet=true;
	}while(0);
	return bRet;
}


Hero* Hero::create(const char* pic,int HP, float speed)
{
	Hero* pRet=new Hero();
	if(pRet && pRet->initWithFile(pic,HP,speed))
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



bool Hero::isActive()
{
	return _active;
}


//void Hero::shoot(float dt)
//{
//	CCPoint position=this->getPosition();
//	Bullet* bullet=Bullet::create("W2.png",_bulletSpeed,1);
//	CCAssert(bullet!=NULL,"W2.png not found");
//	if(bullet)
//	{
//		_allEnemyBulletArray->addObject(bullet);
//		getParent()->addChild(bullet,1,111);       //tag of bullet in gameLayer is 111
//		bullet->setPosition(position);
//
//	}
//	else
//	{
//		delete bullet;
//		bullet=0;
//	}
//
//
//}


void Hero::hurt(float damage)
{
	_HP-=damage;
}



void Hero::destroy()
{
	CCShake* shake=CCShake::create(3.0f,10.0f);
	this->getParent()->getParent()->runAction(shake);

	/*this->removeFromParent();*/
}

int Hero::getDamage()
{
	return 0;
}


void Hero::moveWithDirection(CCPoint direction,float acce)
{
	_velocity=ccp(direction.x*_speed*acce,direction.y*_speed*acce);
}


void Hero::setRotationWithDegree(float degree)
{
	if(this)
	{
	_degree = degree;
	}
	
}

void Hero::stopMove()
{
	_velocity=CCPointZero;
}


float Hero::getSpeed()
{
	return _speed;

}


void Hero::update(float dt)
{
	if(_active)
	{
		_desirePosition=ccpAdd(this->getPosition(),ccpMult(_velocity,dt));
		_desireDegree=_degree;

		this->updateShoot(dt);
	}

	if(_HP<=0)
	{
		_active=false;
	}
}



CCRect Hero::Rect()
{
	return CCRectMake(
		this->getPosition().x-(this->getContentSize().width/4),
		this->getPosition().y-(this->getContentSize().height/4),
		this->getContentSize().width/4,
		this->getContentSize().height/4 );
}



void Hero::shootTowardWithDirection(CCPoint direction)
{
	_shootVector=direction;
	_isShooting=true;
}



void Hero::shootNow()
{
	float mapMax=sqrt((MAPWIDTH*MAPWIDTH)+(MAPHEIGHT*MAPHEIGHT));
	CCPoint actualVector=ccpMult(_shootVector,mapMax);

	_bulletSpeed=1000;
	float duration=mapMax/_bulletSpeed;

	CCPoint position=this->getPosition();
	Bullet* bullet=Bullet::create("W2.png",_bulletSpeed,1);
	CCAssert(bullet!=NULL,"W2.png not found");
	if(bullet)
	{
		_allShipBulletArray->addObject(bullet);
		getParent()->addChild(bullet,1,777);       //tag of bullet in gameLayer is 777
		bullet->setPosition(position);
		/*bullet->setPosition(ccpAdd(this->getPosition(),ccpMult(shootVector,this->getContentSize().height)));*/

		CCMoveBy* move=CCMoveBy::create(duration,actualVector);
		//CCCallFunc* callKill=CCCallFunc::create(bullet,callfunc_selector(Bullet::destroy));
		//bullet->runAction(CCSequence::create(move,callKill,NULL));
		bullet->runAction(move);

	}
	else
	{
		delete bullet;
		bullet=0;
	}


}


bool Hero::shouldShoot()
{
	if(!this->_isShooting)
		return false;

	float SECS_BETWEEN_SHOTS=0.8f;
	if(_timeSinceLastShot>SECS_BETWEEN_SHOTS)
	{
		_timeSinceLastShot=0;
		return true;
	}
	else
	{
		return false;
	}
}



void Hero::updateShoot(float dt)
{
	_timeSinceLastShot+=dt;
	if(this->shouldShoot())
	{
		this->shootNow();
	}
}



void Hero::stopShoot()
{
	_isShooting=false;
}


bool Hero::isShoot()
{
	return _isShooting;
}


void Hero::setShoot(bool val)
{
	if(this)
	{
	_isShooting=val;
	}
}


int Hero::getHP()
{
	return _HP;
}

int Hero::getMaxHP()
{

	return _maxHP;
}


Hero* Hero::sharedHero()
{
	if(!g_hero)
	{
		g_hero=Hero::create("HexPilot.png",HEROMAXLIFE,HEROSPEEED);
		CCAssert(g_hero!=NULL,"HexPilot not found");
	}

	return g_hero;
}


void Hero::resetHero()
{
//	Hero::sharedHero()->removeFromParent();

}