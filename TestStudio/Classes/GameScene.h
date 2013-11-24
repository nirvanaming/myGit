//
//GameScene.h
//
//created by Tim on Nov 23rd 2013
//
#ifndef  _GAME_SCENE_H_
#define  _GAME_SCENE_H_

#include "cocos2d.h"
#include "GameLayer.h"
USING_NS_CC;

class GameScene :
	public CCScene
{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();
	CREATE_FUNC(GameScene);

private:
	GameLayer* _gamelayer;
};

#endif