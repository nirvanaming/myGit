

#ifndef __DIALOGLAYER_H__
#define __DIALOGLAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class DialogLayer: public CCLayerColor
{
    // ģ̬�Ի���˵�
 

   CCMenu *m_pMenu;
    // ��¼�˵����
    bool m_bTouchedMenu;
    
public:
    DialogLayer();
    ~DialogLayer();
    
    virtual bool init();
    

// ��ʼ���Ի�������
    void initDialog();
    
    CREATE_FUNC(DialogLayer);  //old is LAYER_CREATE_FUNC
    
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    

    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void okMenuItemCallback(CCObject *pSender);
    void cancelMenuItemCallback(CCObject *pSender);
};


#endif
