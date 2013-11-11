#pragma once
#include "cocos2d.h"
#include "DPad.h"
#include "RightDPad.h"
#include "HudLayer.h"
#include "Hero.h"
#include "EnemyManage.h"
#include "Enemys.h"

USING_NS_CC;

class GameLayer :
	public CCLayer, public DPadDelegate,public RDpadDelegate
{
public:
	GameLayer(void);
	~GameLayer(void);
	CREATE_FUNC(GameLayer);
	virtual bool init();
	


	//L dpad 
	virtual void didChangeDirectionTo(DPad* dPad,CCPoint direction,float acce);
	virtual void isHoldingDirection(DPad* dPad,CCPoint direction,float acce);
	virtual void simpleDPadTouchEnded(DPad* dPad);

	//R dpad
	virtual void didChangeRotationTo(RightDPad* RDpad,float degree,CCPoint direction);
	virtual void isHoldingRotation(RightDPad* RDpad,float degree,CCPoint direction);
	virtual void RightDPadTouchEnded(RightDPad* RDpad);


	
	CC_SYNTHESIZE(CCTMXTiledMap*,_tileMap,TileMap);
	CC_SYNTHESIZE(HudLayer*,_hud,Hud);
	/*CC_SYNTHESIZE(CCPoint,_spawnPoint,SpawnPoint);*/

	void initBg();
	void initHero();
	void initEnemy();
	void initArray();
	void initMotionStreak();
	virtual void update(float dt);
	void updatePositions();
	void updateRotation();
	void loadEnemy(float dt);
	void setViewpointCenter(CCPoint position);


	bool collide(Unit*a, Unit* b);
	void isCollide();
	virtual void removeInactiveUnit(float dt);

	void updateFollowEnemy();
	void updateRandomMoveEnemy();
	
	void checkIsGo();  //check is game over
	void goCallBack();

	//CC_SYNTHESIZE(Hero*,_hero,Heros);
	

private:
	EnemyManage* _enemyManage;
	int _time;
	CCMotionStreak* _motionStreak;
	CCRect _MapRect;
};

