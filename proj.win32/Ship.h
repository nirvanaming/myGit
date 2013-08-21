//
//Ship.h
//
//created by Tim on Aug 16th 2013
//

#ifndef _SHIP_H_
#define _SHIP_H_

#include "cocos2d.h"
USING_NS_CC;


class Ship:public CCSprite
{

private:
	int m_bulletSpeed;//子弹速度
	
	CCPoint m_appearPosition; //子弹出现位置

	//CCArray* m_allBulletsArray; //保存所有已存在的子弹对象

public:
	Ship();
	~Ship();
	//更新
	virtual void update(float dt);
	//发射子弹
	void shoot(float dt);
	//初始化
	virtual bool init();
	//销毁飞船
	virtual void destroy();
	//碰撞矩形
	virtual CCRect shipRect();
	//构造器
	CREATE_FUNC(Ship);

};
#endif // !_SHIP_H_
