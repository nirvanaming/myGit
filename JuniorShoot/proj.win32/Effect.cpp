//
//Effect.cpp
//
//created by Tim on Aug 25th 2013
//
#include "Effect.h"
using namespace cocos2d;

Effect::Effect(void)
{
}


Effect::~Effect(void)
{
}

Effect* Effect::create()
{
	Effect* effect=new Effect();
	if(effect){
		effect->autorelease();
		return effect;
	}else{
		delete effect;
		effect=NULL;
		return NULL;
	}
}




void Effect::explode(CCNode *parent, CCPoint pos)
{
    	
		CCSprite* m_boom=CCSprite::create();
		       m_boom->retain();
				//add explode effect, define explode effect£º
			m_boom->setPosition(pos);
			parent->addChild(m_boom);
			 CCAnimation* animation = CCAnimation::create();
	      for( int i=1;i<17;i++)
	      {
	          char szName[100] = {0};
	          sprintf(szName, "Download/boom/boom%02d.png", i);
	          animation->addSpriteFrameWithFileName(szName);
	      }
	      // should last n seconds. And there are m frames.
	      animation->setDelayPerUnit(0.6f / 17.0f);
	      animation->setRestoreOriginalFrame(true);
		  CCAction* action=CCSequence::create(CCAnimate::create(animation),
			  CCCallFuncN::create(this,
			  callfuncN_selector(Effect::killSprite)),
			  NULL);
		  m_boom->runAction(action);
		  
    
}

void Effect::killSprite(CCNode *sender)
{
	sender->removeFromParent();
}


void Effect::hit(CCNode* parent, CCPoint pos)
{
	
	CCSprite* hit=CCSprite::create("hit.jpg");
	ccBlendFunc cb={GL_SRC_ALPHA,GL_ONE};
	hit->setBlendFunc(cb);
	hit->setPosition(pos);
	hit->setRotation(CCRANDOM_0_1()*360);
	hit->setScale(0.6);
	parent->addChild(hit,100);

	CCCallFuncN* removeHit=CCCallFuncN::create(hit,callfuncN_selector(Effect::killSprite));
	hit->runAction(CCScaleBy::create(0.3,2,2));
	hit->runAction(CCSequence::create(CCFadeOut::create(0.3),removeHit,NULL));
	
}