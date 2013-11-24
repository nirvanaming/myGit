//
//GameScene.cpp
//
//created by Tim on Nov 23rd 2013
//
#include "GameScene.h"
USING_NS_CC;


GameScene::GameScene(void)
{
}


GameScene::~GameScene(void)
{
}


bool GameScene::init()
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCScene::init());

		_gamelayer=GameLayer::create();
		this->addChild(_gamelayer,0);


		bRet=true;
	}while(0);
	return bRet;

}