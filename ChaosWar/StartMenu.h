//
//StartMenu.h
//
//created by Tim on Nov 4th 2013
//
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class StartMenu :
	public CCLayer
{
public:
	StartMenu(void);
	~StartMenu(void);

	virtual bool init();
	static CCScene* scene();
	void newGame(CCObject* pSender);

	CREATE_FUNC(StartMenu);
};

