//
//GameScene.h
//
//created by Tim on Oct 21st 2013
//
#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
#include "HudLayer.h"
USING_NS_CC;

class GameScene :
	public CCScene
{
public:
	GameScene(void);
	~GameScene(void);
	CREATE_FUNC(GameScene);
	virtual bool init();

	void update(float dt);
	/*GameLayer* _gameLayer;
	HudLayer* _hudLayer;*/

	CC_SYNTHESIZE(GameLayer*,_gameLayer,GameLayer);
	CC_SYNTHESIZE(HudLayer*,_hudLayer,HudLayer);
};

