#ifndef __PAUSELAYER_H__
#define __PAUSELAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class PauseLayer: public CCLayerColor
{
    // ģ̬�Ի���˵�
 

   CCMenu *m_pMenu;
    // ��¼�˵����
    bool m_bTouchedMenu;
    
public:
	PauseLayer();
	~PauseLayer();
    
    virtual bool init();
    

// ��ʼ���Ի�������
    void initDialog();
    
	CREATE_FUNC(PauseLayer);  //old is LAYER_CREATE_FUNC
    
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    

    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    //void okMenuItemCallback(CCObject *pSender);
    void resumeMenuItemCallback(CCObject *pSender);
};


#endif
