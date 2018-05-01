#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;


class StrengthLevelup :
	public cocos2d::CCLayer
{
public:
	StrengthLevelup();

	virtual bool init();

	static cocos2d::CCScene* scene();

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	CREATE_FUNC(StrengthLevelup);

private:
	void showDesp();
	void showFocus(int tag);
	void levelUp(int num=1);
	void levelUpOne();
	void levelUpMax();
	void initLevel();
	void getGold();

	void watch(float dt);
	void showTipMoreDamage(float dt);
	void showTipGoBack(float dt);
	void showTipMoreDamagePoint();
	void showTipGoBackPoint();
	void showAchievementTip(int index);
	void removeNode(CCNode* pSender);

	void moreDamageLevelUp();
	void gotoBattlePage();

	bool isShowAchievementTip;
	int focusTag;
	TouchGroup* ui;
	std::function<void()>  m_successCallback;
	std::function<void()>  m_failCallback;
};
