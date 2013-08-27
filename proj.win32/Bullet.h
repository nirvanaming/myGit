//
//bullet.h
//
//Created by Tim on Aug 14th, 2013
//update on Aug 16th, 2013
//


#ifndef _BULLET_
#define _BULLET_

#include "cocos2d.h"
USING_NS_CC;


class Bullet:public CCLayer
{
public:
	Bullet();
	~Bullet();

public:
	CCSpriteBatchNode* m_bulletSprite;//ʹ��BatchNode�������е��ӵ�������gl�滭���� 
	CCArray* m_allBulletArray;//���������Ѵ��ڵ��ӵ�����

	
	virtual bool init(); //��ʼ��
	//virtual CCRect bulletRect(); //��ײ����
	void addNewBullet(float dt);  //����ӵ�
	void moveBullet(float dt);   //�ƶ��ӵ�
	

	CREATE_FUNC(Bullet);

};

#endif


