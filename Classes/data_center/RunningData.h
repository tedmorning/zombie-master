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

	Reinfoce& getReinfoce(); //���ǿ��ϵͳ��Ϣ
	Resource& getResource(); //�����Դ��Ϣ
	RoleSystem& getRoleSystem(); //��ý�ɫϵͳ��Ϣ
	GameLevel& getGameLevel();	 //�����Ϸ�ؿ���Ϣ
	Shopping& getShopping();     //����̵���Ϣ
	Config& getConfig();        //���������Ϣ
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

