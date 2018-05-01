#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;


class FailLayer :
	public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene(int hero,int level);

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	static FailLayer* create(int hero,int level);

private:

	void roleThreeBlink(float dt);
	void roleTwoBlink(float dt);
	void roleOneBlink(float dt);

	TouchGroup* ui;
	int currentLevel;
	int currentHero;
};
