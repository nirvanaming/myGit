//
//HelloWorldScene.h
//
//created by Tim on Aug 8th 2013
//

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"

class HelloWorld : public cocos2d::CCLayer
{

public:
	
	HelloWorld();
	~HelloWorld();

	cocos2d::CCSprite *pSprite;     //background
	cocos2d::CCSprite *m_pSpriteRe;  //link background
	float pSpriteWidth;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	
	bool m_ispSpriteReload;

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	void pauseLayerCallback(CCObject* pSender);

	//void gameLogic(float dt);

	//void spriteMoveFinished(CCNode* sender);

	void isCollide(float dt);

	void movingBackground(float dt);

	//void removeBoomCallback(CCNode* sender);
	void updateUI(float dt);

	
	//ship moving according to the touch moving
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);


	/***************************************/
	void onEnter();
	void onExit();
	/**************************************/
	


private:

	 //add the player
	Ship* m_ship;
	//bullet
	Bullet* m_bullet;
	//enemy
	Enemy* m_enemy;

	CCSprite* shipIcon1;
	CCSprite* shipIcon2;
	CCSprite* shipIcon3;

	 
	cocos2d::CCPoint mTouchPos;   //initial position
	bool mIsTouching;     //touch or not

	//int Score;   //game score
	CCLabelTTF *m_scoreLabel;  //score label
	CCLabelTTF *m_lifeCountLabel;  //life count label

};

#endif  // __HELLOWORLD_SCENE_H__