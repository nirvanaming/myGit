//
//Bullet.h
//
//created by Tim on Oct 25th 2013
//
#pragma once
#include "unit.h"
USING_NS_CC;

class Bullet :
	public Unit
{
public:
	Bullet(void);
	~Bullet(void);

private:
	float _moveSpeed;
	int _HP;
	int _damage;
	bool _active;

public:
	static Bullet* create(const char* weapon,float speed,int damage);
	virtual bool initWithFile(const char* weapon,float speed,int damage);
	virtual void update(float dt);
	virtual void hurt(float damage);
	virtual void destroy();
	virtual CCRect Rect();
	virtual bool isActive();
	int getDamage();
};

