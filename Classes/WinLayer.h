#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;

struct BattleResult
{
	int hero;
	int level;
	int killedZombieNum;
	int remainBlood;
	int getGoldNum;
};

class WinLayer :
	public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene(BattleResult br);

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	static WinLayer* create(BattleResult br);

private:
	TouchGroup* ui;
	BattleResult m_br;
};
