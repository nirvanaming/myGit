#include "GameLayer.h"
#include "TestScene.h"

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
		_ui->addWidget(dynamic_cast<UILayout*>(GUIReader::shareReader()->widgetFromJsonFile("DemoTest_1.json")));

		UIButton* room1=dynamic_cast<UIButton*>(_ui->getWidgetByName("room_01"));
		room1->addReleaseEvent(this,coco_releaseselector(GameLayer::testSceneCallBack));    //click the first room and message can enter to another scene

		UIImageView* message=dynamic_cast<UIImageView*>(_ui->getWidgetByName("messageIcon"));
		message->addReleaseEvent(this,coco_releaseselector(GameLayer::testSceneCallBack));

		UILabelBMFont* name=dynamic_cast<UILabelBMFont*>(_ui->getWidgetByName("LabelBMFont_name"));
		CCLog("%d",name->getStringValue());
		name->setText("timtim");    /////////////////set the name in here

		bRet=true;
	}while(0);
	return bRet;
}


void GameLayer::testSceneCallBack(CCObject* pSender)
{
	CCScene* pScene=TestScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}
