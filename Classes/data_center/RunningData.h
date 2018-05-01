#ifndef  ___RUNNING_DATA_h___
#define  ___RUNNING_DATA_h___

#include "tool.h"
#include "Reinfoce.h"
#include "Resource.h"
#include "RoleSystem.h"
#include "GameLevel.h"
#include "Shopping.h"
#include "Config.h"
#include "BattleData.h"
#include "Achievement.h"


class RunningData : public CCObject
{
public:
	static RunningData* getInstance();
	bool init();

	Reinfoce& getReinfoce(); //获得强化系统信息
	Resource& getResource(); //获得资源信息
	RoleSystem& getRoleSystem(); //获得角色系统信息
	GameLevel& getGameLevel();	 //获得游戏关卡信息
	Shopping& getShopping();     //获得商店信息
	Config& getConfig();        //获得配置信息
	BattleData& getBattleData();
	Achievement& getAchievement();

	int currentHero;
	bool isMainTip;
	bool isStrengthLevelupPageTip;
	bool isFromStrengthLevelupPage;
	bool isFromGameMainPage;


private:
	Reinfoce m_reinfoce;
	Resource m_resource;
	RoleSystem m_roleSystem;
	GameLevel m_gameLevel;
	Shopping m_shopping;
	Config m_config;
	BattleData m_battleData;
	Achievement m_achievement;
	
};

#endif

