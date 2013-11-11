//
//Enemys.cpp
//
//Created by Tim on Oct 28th 2013
//
#include "Enemys.h"
#include "Effects.h"
#include "CCShake.h"
#include "Config.h"
using namespace std;
USING_NS_CC;

#define PI 3.14
#define DeltaRadians PI/180
#define DeltaDegree 1

Enemys::Enemys(void):
	_active(true),
	_speed(200),
	_HP(1),
	_moveType(0),
	_scoreValue(200),
	_directionSpeed(ccp(1,1)),
	_damage(1)

{
}


Enemys::~Enemys(void)
{
	
}


bool Enemys::initWithFile(EnemyType type)
{
	bool sRet=false;
	do{
		CC_BREAK_IF(!Unit::init());
		_HP=type.hp;
		_moveType=type.moveType;
		_scoreValue=type.scoreValue;

		this->initWithSpriteFrameName(type.textureName.c_str());
   
    sRet=true;
	}while(0);

	return sRet;
}

Enemys* Enemys::create(EnemyType type)
{
	Enemys* enemy=new Enemys();
	if(enemy&&enemy->initWithFile(type))
	{
		enemy->autorelease();
		return enemy;
	}else{
		delete enemy;
		enemy=NULL;
		return NULL;
         }
}

void Enemys::update(float dt)
{
	if(_HP<=0)
		{
			_active=false;
		}
}


void Enemys::hurt(float damage)
{
	/*PopNumbers* popN=PopNumbers::create(200);
	popN->setPosition(this->getPosition());
	this->getParent()->addChild(popN,1000);*/

	//showDamage(damage,this);
	popDamage(damage,this->getParent(),this->getPosition());
   _HP-=damage;
}


void Enemys::destroy()
{
	Config::sharedConfig()->setScore(_scoreValue);
	CCShake* shake=CCShake::create(0.2f,10.0f);
	this->getParent()->getParent()->runAction(shake);


	Effects* effect=Effects::create();
	effect->explode(this->getParent(),this->getPosition());
	_allEnemyArray->removeObject(this);
	this->removeFromParent();
	
}



CCRect Enemys::Rect()
{
	return CCRectMake(
		this->getPosition().x-(this->getContentSize().width/2),
		this->getPosition().y-(this->getContentSize().height/2),
		this->getContentSize().width/2,
		this->getContentSize().height/2 );
}


bool Enemys::isActive()
{
	return _active;
}


int Enemys::getMoveType()
{

	return _moveType;
}

void Enemys::sharedEnemys()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Enemy.plist","Enemy.png");
}


//void Enemys::seekHero(Hero* hero)
//{
//	if(hero)
//	{
//		_target=hero;
//	}
//	else
//	{
//		_target=NULL;
//	}
//}

float Enemys::calcAngel(CCPoint target)
{
	float r=PI;
	CCPoint p2=ccpSub(target,this->getPosition());
	r=ccpAngle(_directionSpeed,p2);
	return r;
}



int Enemys::calcDirection(CCPoint target)
{
	CCPoint p2=ccpSub(target,this->getPosition());
	if(ccpCross(_directionSpeed,p2)>0)
	{
		return -1; //在opengl的右手坐标系中，向量叉乘大于0表示逆时针方向
	}
	else if(ccpCross(_directionSpeed,p2)<0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void Enemys::trackMove(Hero* hero)
{
	if(hero)
	{
	_target=hero;
	}
	do
	{
		if(_target)
		{
			/*if(!(_target->isActive()))
			{
				_target=NULL;
				break;
			}*/

			//step1: 确定角度
			float _rad=calcAngel(_target->getPosition());

			//if(_rad && _rad>=PI/2)
			//{
			//	//角度大于90的时候放弃，不追踪
			//	_target=NULL;
			//	break;
			//}

			float _deg=CC_RADIANS_TO_DEGREES(_rad);

			float deltaR=_rad<DeltaRadians?_rad:DeltaRadians;
			float deltaD=_deg<DeltaDegree?_deg:DeltaDegree;

			//step2:确定方向
			int actualDirection=calcDirection(_target->getPosition());
			switch(actualDirection)
			{
			case -1:
				{
					_directionSpeed=ccpRotateByAngle(_directionSpeed,ccp(0,0),deltaR);
					this->setRotation(this->getRotation()-deltaD);
					break;
				}

			case 1:
				{
					_directionSpeed=ccpRotateByAngle(_directionSpeed,ccp(0,0),-deltaR);
					this->setRotation(this->getRotation()+deltaD);
					break;
				}
			default:
				break;

			}

		}else{
			hero->runAction(CCMoveTo::create(10,ccp(-MAPWIDTH,-MAPHEIGHT)));
		}

	}while(0);
	this->setPosition(ccpAdd(getPosition(),_directionSpeed));
}




//void Enemys::showDamage(int damage,CCSprite* pObj)
//{
//	if(damage>0)
//	{
//		char char_damage[100]={0};
//		sprintf(char_damage,"%d",damage,char_damage);
//
//		CCString* numberstr=CCString::create(char_damage);
//		PopNumbers* damageHurt=PopNumbers::create(damage);
//
//		damageHurt->numbers->setPosition(ccp(pObj->getContentSize().width/2,
//			pObj->getContentSize().height*1.5f));
//
//		//can add bezier run
//		ccBezierConfig bezier;
//		bezier.controlPoint_1=CCPointMake(50,pObj->getContentSize().height*2.0f);
//		bezier.controlPoint_2=CCPointMake(pObj->getContentSize().width/2,pObj->getContentSize().height);
//		CCActionInterval* bezier_act=CCBezierTo::create(2.5f,bezier);
//
//		CCActionInterval* scale_act=CCScaleTo::create(2.0f,1.5f);
//		CCActionInterval* scale_actby=CCScaleBy::create(1.0f,2.0f);
//
//		CCActionInterval* fade_act=CCFadeIn::create(2.0f);
//		CCActionInterval* fade_act2=CCFadeOut::create(2.0f);
//
//		CCFiniteTimeAction* actBackFun=CCCallFuncO::create(pObj,callfuncO_selector(Enemys::RemoveShowDamage),pObj);
//		damageHurt->numbers->runAction(CCSequence::create(scale_actby,scale_actby->reverse(),NULL));
//		damageHurt->numbers->runAction(fade_act2);
//		for(unsigned int i=0;i<numberstr->length();i++)
//		{
//			CCActionInterval* fade_actby_back=fade_act->reverse();
//			damageHurt->numbers->getChildByTag(10+i)->runAction(fade_actby_back);
//		}
//		damageHurt->numbers->runAction(CCSequence::create(bezier_act,actBackFun,NULL));
//		pObj->addChild(damageHurt->numbers,10,12);
//
//	}
//
//}


//void Enemys::RemoveShowDamage(CCObject* pObj)
//{
//	CCSprite* enemy=(CCSprite*)pObj;
//	enemy->removeChildByTag(12);
//}



void Enemys::popDamage(int damage,CCNode* parent,CCPoint pos)
{
	CCLabelAtlas* label=CCLabelAtlas::create("1:","set1_player_hud3.png",14,21,'0');
	parent->addChild(label,101);
	label->setScale(4.0f);
	label->setPosition(pos);
	char t[10];
	sprintf(t, "%d", damage);
	label->setString(t);

	CCActionInterval* damageFadeOut=CCFadeOut::create(0.5f);
	CCActionInterval* damageScaleTo=CCScaleTo::create(0.5f,0.5f);
	CCCallFuncN* removeDamage=CCCallFuncN::create(label,callfuncN_selector(Enemys::killPopDamage));
	label->runAction(damageScaleTo);
	label->runAction(CCSequence::create(damageFadeOut,removeDamage,NULL));
}



void Enemys::killPopDamage(CCNode* pSender)
{
	pSender->removeFromParent();
}


int Enemys::getDamage()
{
	return _damage;
}