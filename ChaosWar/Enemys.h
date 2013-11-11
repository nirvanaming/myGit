//
//Enemys.h
//
//created by Tim on Oct 28th 2013
//
#pragma once
#include "unit.h"
#include "Config.h"
#include "Hero.h"
USING_NS_CC;

class Enemys :
	public Unit
{
public:
	Enemys(void);
	~Enemys(void);

private:
	bool _active;
	float _speed;
	int _HP;
	int _moveType;
	int _scoreValue;
	int _damage;

	Hero* _target;
	CCPoint _directionSpeed;

public:
	static Enemys* create(EnemyType type);
	virtual bool initWithFile(EnemyType type);
	virtual void update(float dt);
	virtual void hurt(float damage);
	virtual void destroy();
	virtual CCRect Rect();
	virtual bool isActive();
	static void sharedEnemys();
	int getMoveType();
	virtual int getDamage();

	//void seekHero(Hero* hero);
	float calcAngel(CCPoint target);
	int calcDirection(CCPoint target);
	void trackMove(Hero* hero);
	
	/*void showDamage(int damage, CCSprite* pObj);
	void RemoveShowDamage(CCObject* pObj);*/

	void popDamage(int damage,CCNode* parent,CCPoint pos);
	void killPopDamage(CCNode* pSender);


};

