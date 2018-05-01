#include "RunningData.h"

RunningData* ins = NULL;

bool RunningData::init()
{	
	
	if(!::checkCacheFile())
	{
		moveFile("reinfoceSystem.json");
		moveFile("reinfoceRule.json");
		moveFile("resource.json");
		moveFile("role.json");
		moveFile("gameLevel.json");
		moveFile("levelInfos.json");
		moveFile("shopping.json");
		moveFile("config.json");
		moveFile("battle.json");
		moveFile("achievement.json");
	}

	m_reinfoce.init();
	m_resource.init();
	m_roleSystem.init();
	m_gameLevel.init();
	m_shopping.init();
	m_config.init();
	m_battleData.init();
	m_achievement.init();

	isMainTip = false;
	isStrengthLevelupPageTip = false;
	isFromStrengthLevelupPage = false;
	currentHero = -1;
	isFromGameMainPage = false;
	return true;
}

RunningData* RunningData::getInstance()
{
	if( ins == NULL ) {
		ins = new RunningData();
		ins->init();
	}

	return ins;
}

Reinfoce& RunningData::getReinfoce()
{
	return m_reinfoce;
}

Resource& RunningData::getResource()
{
	return m_resource;
}

RoleSystem& RunningData::getRoleSystem()
{
	return m_roleSystem;
}

GameLevel& RunningData::getGameLevel()
{
	return m_gameLevel;
}

Shopping& RunningData::getShopping()
{
	return m_shopping;
}

Config& RunningData::getConfig()
{
	return m_config;
}

BattleData& RunningData::getBattleData()
{
	return m_battleData;
}

Achievement& RunningData::getAchievement()
{
	return m_achievement;
}