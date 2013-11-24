//
//TestScene.h
//
//created by Tim on Nov 24th 2013
//
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class TestScene :
	public CCLayer
{
public:
	TestScene(void);
	~TestScene(void);

	virtual bool init();
	static CCScene* scene();
	CREATE_FUNC(TestScene);

	void gameLayerCallBack(CCObject* pSender);
};

