//
//Ship.h
//
//created by Tim on Aug 16th 2013
//

#ifndef _SHIP_H_
#define _SHIP_H_

#include "cocos2d.h"
USING_NS_CC;


class Ship:public CCLayer
{

public:
	Ship();
	~Ship();
public:
	
	static Ship* sharedShip;
	//init
	virtual bool init();
	//create ship
	static Ship* create();
	//rect
	virtual CCRect shipRect();
	//move ship
	void moveTo(CCPoint p);
	//is hurt
	void Hurt();
	//ship hp
    //int shipHP;
	//gameoverscene callback
	void GOCallBack(CCNode* pSender);
	

};
#endif // !_SHIP_H_
