#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "data_center\RunningData.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;


class LevelInstruction :
	public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene(bool isrepeat);

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	static LevelInstruction* create(bool isrepeat);

private:

	void roleChat();
	void roleShow();
	void goBattle();
	void bgShow(LevelInfo& li);
	void watch(float dt);

	TouchGroup* ui;
public:

	bool isBuyFail;
	bool ischat;
	bool isrepeatGame;
	std::function<void()> m_successCallback;
	std::function<void()> m_failCallback;
};
