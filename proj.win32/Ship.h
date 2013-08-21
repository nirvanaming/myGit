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
	int m_bulletSpeed;//�ӵ��ٶ�
	
	CCPoint m_appearPosition; //�ӵ�����λ��

	//CCArray* m_allBulletsArray; //���������Ѵ��ڵ��ӵ�����

public:
	Ship();
	~Ship();
	//����
	virtual void update(float dt);
	//�����ӵ�
	void shoot(float dt);
	//��ʼ��
	virtual bool init();
	//���ٷɴ�
	virtual void destroy();
	//��ײ����
	virtual CCRect shipRect();
	//������
	CREATE_FUNC(Ship);

};
#endif // !_SHIP_H_
