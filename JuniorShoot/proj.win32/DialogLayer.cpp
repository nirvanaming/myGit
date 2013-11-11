//  DialogLayer.cpp
//  ModalDialogDemo
//
//  Created by Tom on 12-5-28.
//  Copyright (c) 2012Äê __MyCompanyName__. All rights reserved.
//

#include "DialogLayer.h"

DialogLayer::DialogLayer()
{
}

DialogLayer::~DialogLayer()
{
}

bool DialogLayer::init()
{
    bool bRet = false;
    
    do {
   

     CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125)));
        
        this->initDialog();
        
        bRet = true;
    } while 

(0);
    
    return bRet;
}

void DialogLayer::initDialog()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	CCLabelTTF *label = CCLabelTTF::create("Are u sure exit?", "", 30);
    label->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 50));
    this->addChild(label,4);
    
	CCMenuItemFont *okMenuItem = CCMenuItemFont::create("OK",this, menu_selector(DialogLayer::okMenuItemCallback));
//	okMenuItem->setFontSize(20);
    

okMenuItem->setPosition(ccp(winSize.width / 2 - 100, winSize.height / 2 - 50));
    
	CCMenuItemFont *cancelMenuItem = 

CCMenuItemFont::create("Cancel", this, menu_selector(DialogLayer::cancelMenuItemCallback));
    cancelMenuItem->setPosition(ccp(winSize.width /2 + 100, winSize.height / 2 - 50));
    
	m_pMenu = CCMenu::create(okMenuItem, cancelMenuItem, NULL);
    m_pMenu->setPosition(CCPointZero);
    
this->addChild(m_pMenu,4);
}

void DialogLayer::onEnter()
{
    CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

void DialogLayer::onExit()
{
    CCLayerColor::onExit();
    

CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool DialogLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void DialogLayer::ccTouchMoved

(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void DialogLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, 

pEvent);
        m_bTouchedMenu = false;
    }
}

void DialogLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if 

(m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}



void DialogLayer::okMenuItemCallback(cocos2d::CCObject *pSender)
{
    // click OK to Exit(copy the old func)
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void DialogLayer::cancelMenuItemCallback(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(false);
	CCDirector::sharedDirector()->resume();
}
