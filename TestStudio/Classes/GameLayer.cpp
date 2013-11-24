#include "GameLayer.h"
USING_NS_CC;
USING_NS_CC_EXT;

GameLayer::GameLayer(void)
{
}


GameLayer::~GameLayer(void)
{
}


bool GameLayer::init()
{
	bool bRet=false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		_ui=UILayer::create();
		this->addChild(_ui,0,100);
		_ui->addWidget(CCSGUIReader::shareReader()->widgetFromJsonFile("DemoTest_1.json"));

		bRet=true;
	}while(0);
	return bRet;
}