//
//HudLayer.h
//
//created by Tim on Oct 21st 2013
//
#pragma once
#include "cocos2d.h"
#include "DPad.h"
#include "RightDPad.h"
#include "Hero.h"
USING_NS_CC;

class HudLayer :
	public CCLayer
{
public:
	HudLayer(void);
	~HudLayer(void);

	CREATE_FUNC(HudLayer);
	bool init();
	CC_SYNTHESIZE(DPad*,_dpad,DPAD);
	CC_SYNTHESIZE(RightDPad*,_rdpad,RDPAD);
	void initDpad();

	virtual void draw();

};

