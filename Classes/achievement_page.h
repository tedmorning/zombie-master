#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;


class AchievementPage :
	public cocos2d::CCLayer
{
public:

	virtual bool init();
	static cocos2d::CCScene* scene();
	void buttonClicked(CCObject *pSender, TouchEventType eType);

	CREATE_FUNC(AchievementPage);
private:
	void scrollEvent(CCObject *pSender, ScrollviewEventType type);
	void sliderEvent(CCObject *pSender, SliderEventType type);

	TouchGroup* ui;
};
