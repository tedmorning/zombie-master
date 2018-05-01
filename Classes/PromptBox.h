#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;

class PromptBox :
	public cocos2d::CCLayer
{
public:
	virtual bool init();

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	CREATE_FUNC(PromptBox);

private:
	TouchGroup* ui;

};
