#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;

class ShoppingLayer :
	public cocos2d::CCLayer
{
public:
	virtual bool init();

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	void setSuccessCallFun(std::function<void()> sfun);
	void setFailCallFun(std::function<void()> sfun);

	CREATE_FUNC(ShoppingLayer);

private:

	void removeNode(CCNode* pSender);
	void showShoppingTip(bool isSuccess);

	void buySuccess(float dt);

	TouchGroup* ui;

	std::function<void()> m_successFun;
	std::function<void()> m_failFun;

	CCObject* m_target;

	 void successCallBack(bool buyOver);
	std::string payID;
};
