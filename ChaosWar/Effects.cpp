//
//Effect.cpp
//
//created by Tim on Oct 31st 2013
//
#include "Effects.h"
USING_NS_CC;


Effects::Effects(void)
{
}


Effects::~Effects(void)
{
}


Effects* Effects::create()
{
	Effects* effect=new Effects();
	if(effect){
		effect->autorelease();
		return effect;
	}else{
		delete effect;
		effect=NULL;
		return NULL;
	}
}



void Effects::explode(CCNode *parent, CCPoint pos)
{
	 // ��һ֡
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("explosion_01.png");
	CCAssert(pFrame!=NULL,"explosion_01.png not found");
    CCSprite *explosion = CCSprite::createWithSpriteFrame(pFrame);
    parent->addChild(explosion);
    explosion->setPosition(pos);
    
    CCSize cs = explosion->getContentSize();
    
    // ���֮��Ļص�
    CCCallFuncN *removeFunc =  CCCallFuncN::create(explosion, callfuncN_selector(Effects::killSprite));
    
    // ��ը����
    CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName("Explosion");
	CCAssert(animation!=NULL,"Explosion not found");
    explosion->runAction(CCSequence::create(CCAnimate::create(animation), removeFunc, NULL));


}



void Effects::killSprite(CCNode *pSender)
{
//    CCLOG("remove effect");
    pSender->removeFromParent();
}


//�������뻺��
void Effects::sharedExplosion()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("explosion.plist");
    CCArray *animFrames = CCArray::create();
    
    char str[64] = {0};
    for (int i = 1; i < 36; ++i) {
        sprintf(str, "explosion_%02d.png", i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
        animFrames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.04);
    
    // ֡��������
    CCAnimationCache::sharedAnimationCache()->addAnimation(animation, "Explosion");
    
}