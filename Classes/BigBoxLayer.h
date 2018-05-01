#pragma once
#include "cocos2d.h"
USING_NS_CC;
class BigBoxLayer:public CCLayer
{
public:
	BigBoxLayer();
	~BigBoxLayer();
	bool init();
	CREATE_FUNC(BigBoxLayer);
	void onClick(CCObject * obj);
	std::function<void()> m_callFun;
	void setCallFun(std::function<void()> callFun);
};

