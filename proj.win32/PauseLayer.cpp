

#include "PauseLayer.h"
#include "HelloWorldScene.h"

PauseLayer::PauseLayer()
{
}

PauseLayer::~PauseLayer()
{
}

bool PauseLayer::init()
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

void PauseLayer::initDialog()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage *resumeButton=CCMenuItemImage::create("Download/Play.png","Download/Play.png",
		this,
		menu_selector(PauseLayer::resumeMenuItemCallback));

	m_pMenu = CCMenu::create(resumeButton, NULL);        //ǧ����CCMenu* m_pMenu�������壬��Ϊͷ�ļ����Ѿ�������������������Ļ��ж�����
    m_pMenu->setPosition(ccp(size.width/2,size.height/2));

this->addChild(m_pMenu,5);
}

void PauseLayer::onEnter()
{
    CCLayerColor::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

void PauseLayer::onExit()
{
    CCLayerColor::onExit();
    

CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


bool PauseLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void PauseLayer::ccTouchMoved

(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void PauseLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, 

pEvent);
        m_bTouchedMenu = false;
    }
}

void PauseLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if 

(m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}





void PauseLayer::resumeMenuItemCallback(cocos2d::CCObject *pSender)

{
	this->getParent()->getChildByTag(10)->setVisible(true);
    this->removeFromParentAndCleanup(false);
	CCDirector::sharedDirector()->resume();
	
}