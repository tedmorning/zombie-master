#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;


class ChallengeLayer :
	public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene(int hero,int levelint, int repeatTimes, int totolGold);

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	static ChallengeLayer* create(int hero,int level,int repeatTimes, int totolGold);

private:
	
	int currentLevel;
	int currentHero;
	int  repeatTimes;
	int totolGold;
	
	TouchGroup* ui;

};
