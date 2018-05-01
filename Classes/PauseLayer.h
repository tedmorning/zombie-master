#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;


class PauseLayer :
	public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	CREATE_FUNC(PauseLayer);

private:

	void shoppingSupply(int tag);

	std::function<void()> m_successCallback;
		//计费失败后回调
	std::function<void()> m_failCallback;
	TouchGroup* ui;
};
