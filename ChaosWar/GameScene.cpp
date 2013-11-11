//
//GameScene.cpp
//
//created by Tim on Oct 21st 2013
//
#include "GameScene.h"


GameScene::GameScene(void)
{
	_gameLayer=NULL;
	_hudLayer=NULL;
}


GameScene::~GameScene(void)
{
	this->unscheduleUpdate();
}

void GameScene::update(float dt)
{
	//_gameLayer->setViewpointCenter(_hudLayer->getHeros()->getPosition());
}

bool GameScene::init()
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCScene::init());
		_gameLayer=GameLayer::create();
		CC_BREAK_IF(!_gameLayer);
		this->addChild(_gameLayer,0);

		_hudLayer=HudLayer::create();
		this->addChild(_hudLayer,1);

		_hudLayer->getDPAD()->setDelegate(_gameLayer);
		_hudLayer->getRDPAD()->setRDelegate(_gameLayer);
		_gameLayer->setHud(_hudLayer);
		//_hudLayer->getHeros()->setPosition(_gameLayer->getSpawnPoint());

		this->scheduleUpdate();

		bRet=true;
	}while(0);
	return bRet;
}