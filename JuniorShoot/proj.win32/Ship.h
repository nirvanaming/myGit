//
//Ship.h
//
//created by Tim on Aug 16th 2013
//

#ifndef _SHIP_H_
#define _SHIP_H_

#include "Unit.h"
#include "cocos2d.h"
USING_NS_CC;


class Ship:public Unit
{

public:
	Ship();
	~Ship();

private:
	int m_HP;
	bool m_canBeAttack;
public:
	bool m_active;
	static Ship* sharedShip;
	//init
	virtual bool initWithFile(const char* pic);
	//create ship
	static Ship* create(const char* pic);
	virtual void update(float dt);
	
	//move ship
	void moveTo(CCPoint p);
	//is hurt
	virtual void hurt();
	virtual void destroy();
	virtual CCRect Rect();
	virtual bool isActive();

	
	void GOCallBack(CCNode* pSender);

	virtual void shoot(float dt);

	virtual void makeAttack(CCNode* pSender);
	

};
#endif // !_SHIP_H_
