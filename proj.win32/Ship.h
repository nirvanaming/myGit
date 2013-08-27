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
	//��ʼ��
	virtual bool init();
	//�����ɻ�����
	static Ship* create();
	//��ײ����
	virtual CCRect shipRect();
	//�ƶ��ɻ�
	void moveTo(CCPoint p);
	//������
	void Hurt();
	//�ɻ�����
	int shipHP;
	//gameoverscene callback
	void GOCallBack(CCNode* pSender);
	

};
#endif // !_SHIP_H_
