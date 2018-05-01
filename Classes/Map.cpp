#include "Map.h"


Map* Map::create(BattleManage *battle)
{
	Map* map = new Map();
	if (map->init(battle))
	{
		map->autorelease();
		return map;
	}
	CC_SAFE_DELETE(map);
	return NULL;
}

Map::Map():
battle(battle),
wangTimeAxis(0)
{

}

Map::~Map()
{
	
}

bool Map::init(BattleManage *battle)
{
	this->battle = battle;
	initMap1();

	for (char i = 0; i < WANG_LENGTH; i++)
	{
		//sprintf("wang%s", i + 1);
		wang[i] = CCSprite::create("");
	}
	return true;
}

void Map::initMap1()
{
	//´°¿Ú´óÐ¡
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	/*
	//±³¾°Í¼Æ¬
	CCSprite* bg = CCSprite::create("bg1.png");
	bg->setAnchorPoint(ccp(0, 0));
	battle->addChild(bg, MAP_BG_zOrder);

	//ÅÚÌ¨Í¼Æ¬
	CCSprite* paotai = CCSprite::create("paotai.png");
	paotai->setAnchorPoint(ccp(0.5f, 0));
	paotai->setPosition(ccp(visibleSize.width/2, 0));
	battle->addChild(paotai, MAP_BG_zOrder);

	*/
	
}

void Map::updata(float dt)
{

}

void Map::setWang()
{
	if (wangTimeAxis > 0)
	{
		return;
	}
	wangTimeAxis = 0.5f;

}