//
//Hero.h
//
//created by Tim on Oct 21st 2013
//
#pragma once
#include "Defines.h"
#include "unit.h"
USING_NS_CC;

class Hero :
	public Unit
{
public:
	Hero(void);
	~Hero(void);

	static Hero* sharedHero();

	virtual bool initWithFile(const char* pic,int HP,float speed);
	static Hero* create(const char* pic,int HP,float speed);

	virtual bool isActive();
	virtual void hurt(float damage);
	virtual void destroy();
	virtual CCRect Rect();
	virtual int getDamage();

	//void shoot(float dt);
	void moveWithDirection(CCPoint direction,float acce);
	void setRotationWithDegree(float degree);
	void stopMove();
	float getSpeed();
	void update(float dt);

	CC_SYNTHESIZE(CCPoint,_velocity,Velocity);
	CC_SYNTHESIZE(CCPoint,_desirePosition,DesirePosition);
	CC_SYNTHESIZE(float,_degree,Degree);
	CC_SYNTHESIZE(float,_desireDegree,DesireDegree);

	//new added for shoot
	
	void shootTowardWithDirection(CCPoint direction);
	void shootNow();
	bool shouldShoot();
	void updateShoot(float dt);
	void stopShoot();
	bool isShoot();
	void setShoot(bool val);
	int getHP();
	int getMaxHP();

	void resetHero();

private:
	int _HP;
	int _maxHP;
	bool _active;
	float _speed;


	//new add for shoot
	CCPoint _shootVector;    //shoot direction
	float _timeSinceLastShot;
	bool _isShooting;
	float _bulletSpeed;


	
};

