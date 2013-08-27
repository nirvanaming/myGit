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
	//初始化
	virtual bool init();
	//创建飞机对象
	static Ship* create();
	//碰撞矩形
	virtual CCRect shipRect();
	//移动飞机
	void moveTo(CCPoint p);
	//被击中
	void Hurt();
	//飞机生命
	int shipHP;
	//gameoverscene callback
	void GOCallBack(CCNode* pSender);
	

};
#endif // !_SHIP_H_
