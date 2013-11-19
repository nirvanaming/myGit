//
//GameOver.h
//
//created by Tim on Nov 6th 2013
//
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GameOver :
	public CCLayer
{
public:
	GameOver(void);
	~GameOver(void);

	virtual bool init();
	static CCScene* createScene();

	void restartGame(CCObject* pSender);

	CREATE_FUNC(GameOver);
};

