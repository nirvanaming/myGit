//
//HelloWorldScene.h
//
//created by Tim on Aug 8th 2013
//

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Ship.h"
#include "Enemy.h"
#include "Unit.h"
#include "EnemyActionMag.h"
class HelloWorld : public cocos2d::CCLayer
{

public:
	
	HelloWorld();
	~HelloWorld();

	cocos2d::CCSprite *pSprite;     //background
	cocos2d::CCSprite *m_pSpriteRe;  //link background
	float pSpriteWidth;

    virtual bool init();  

	
	bool m_ispSpriteReload;

    static cocos2d::CCScene* scene();

    // a selector callback
    void menuCloseCallback(CCObject* pSender);

	void pauseLayerCallback(CCObject* pSender);

	void isCollide();

	void movingBackground(float dt);

	//void removeBoomCallback(CCNode* sender);
	void updateUI();

	//void addEnemy(float dt);

	bool collide(Unit*a, Unit* b);

	virtual void update(float dt);

	virtual void removeInactiveUnit(float dt);
	virtual void checkReborn();

	Ship* getShip();
	void scoreCounter(float dt);
	
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
	int m_time;
	CCRect m_screenRect;

	 
	cocos2d::CCPoint mTouchPos;   //initial position
	bool mIsTouching;     //touch or not

	//int Score;   //game score
	CCLabelTTF *m_scoreLabel;  //score label
	CCLabelTTF *m_lifeCountLabel;  //life count label
	EnemyActionMag* m_EnemyActionMag;

};

#endif  // __HELLOWORLD_SCENE_H__