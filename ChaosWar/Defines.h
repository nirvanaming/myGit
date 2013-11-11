//
//Defines.h
//
//created by Tim on Oct 22nd 2013
//
#pragma once
#include "cocos2d.h"
USING_NS_CC;
//convenience measurements
#define MAPWIDTH 1000.0f
#define MAPHEIGHT 1000.0f
#define HEROMAXLIFE 5
#define HEROSPEEED 5.0f
#define SCREEN CCDirector::sharedDirector()->getWinSize()
#define CENTER ccp(SCREEN.width/2,SCREEN.height/2)
#define CURTIME GetCurTime()
//#define CURTIME do{                                                \
//timeval time;                                                      \
//gettimeofday(&time,NULL);                                          \
//unsigned long millisecs=(time.tv_sec*1000)+(time.tv_sec/1000);     \
//return (float)millisecs;                                           \
//}while(0)                                                          \

//convenience functions
#ifndef UINT64_C
#define UINT64_C(val) val##ui64
#endif
#define random_range(low,high) (rand()%(high-low+1))+low
#define frandom (float)rand()/UINT64_C(0x100000000)
#define frandom_range(low,high) ((high-low)*frandom)+low

//enumerations
//typedef enum _ActionState{
//	kActionStateNone=0,
//	kActionStateIdle,
//	kActionStateShoot,
//	kActionStateMove,
//	kActionStateHurt,
//	kActionStateExplode
//}ActionState;

//structures
//typedef struct _BoundingBox{
//	CCRect actual;
//	CCRect original;
//}BoundingBox;

inline float GetCurTime()
{
	timeval time;
	gettimeofday(&time,NULL);
	unsigned long millisecs=(time.tv_sec*1000)+(time.tv_usec/1000);
	return (float)millisecs;
};