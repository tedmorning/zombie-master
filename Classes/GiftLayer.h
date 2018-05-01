#ifndef _GIFTLAYER_H_
#define _GIFTLAYER_H_
#include "cocos2d.h"
#include "JniCommon.h"
#include "cocos-ext.h"
using namespace cocos2d::ui;
USING_NS_CC;

class GiftLayer:public CCLayer
{
public:
	GiftLayer();
	~GiftLayer();
	static GiftLayer* create(PayType payType);
	bool init(PayType payType);
	void onButtonClick(CCObject * obj,TouchEventType eventType);

	void onClose(CCObject * obj, TouchEventType eventType);

	
	PayType m_payType;


	std::function<void()> m_successFun;
	std::function<void()> m_failFun;
	bool m_hasSuccessFun;
	bool m_hasfailFun;
	void setSuccessCallFun(std::function<void()> sfun);
	void setFailCallFun(std::function<void()> sfun);

	void payCallBack(bool result);

	void callSuccess(float dt);
	static CCScene* scene(GiftLayer * layer);
	bool m_isScene;
	TouchGroup* m_pUiLayer;
	void onExit();

	
};

#endif