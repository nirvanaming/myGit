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
    	
		CCSprite* m_boom=CCSprite::create("Download/boom/boom00.png");
		       m_boom->retain();
				//在这里增加爆炸动画效果，add action
				//定义动画效果：
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