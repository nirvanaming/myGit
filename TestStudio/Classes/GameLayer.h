#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GameLayer :
	public CCLayer
{
public:
	GameLayer(void);
	~GameLayer(void);

	virtual bool init();
	CREATE_FUNC(GameLayer);


private:
	UILayer* _ui;

};

