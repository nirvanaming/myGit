#ifndef _MENU_H_
#define _MENU_H_

#include "cocos2d.h"

class SettingScene:public cocos2d::CCScene
{
public:
	SettingScene();
	~SettingScene();

	virtual void onEnter();
};



class MenuLayer:public cocos2d::CCLayer
{
public:
	MenuLayer();
	~MenuLayer();
	
	//virtual bool init();

	//static cocos2d::CCScene* scene();

	void HelloWorldCallBack(CCObject* pSender);

	//CREATE_FUNC(MenuLayer);

};

#endif // !_MENU.H_
