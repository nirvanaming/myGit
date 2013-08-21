#ifndef _GAME_OVER_SCENE_H_
#define _GAME_OVER_SCENE_H_

#include "cocos2d.h"

class GameOverLayer: public cocos2d::CCLayerColor
{
public:
	GameOverLayer():_label(NULL){};

	virtual ~GameOverLayer();

	bool init();

	CREATE_FUNC(GameOverLayer);

	void gameOverDone();

	void PlayScreenCallBack(CCObject *pSender);

	CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*,_label,label);
};

class GameOverScene:public cocos2d::CCScene
{
public:
	GameOverScene():_layer(NULL){};
	~GameOverScene();
	bool init();
	CREATE_FUNC(GameOverScene);

	CC_SYNTHESIZE_READONLY(GameOverLayer*,_layer,layer);
};

#endif