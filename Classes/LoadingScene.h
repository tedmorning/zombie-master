#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;


class LoadingLayer :
	public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(LoadingLayer);

private:
	
	void showDot(float dt);
	void loading(float dt);
	void hideDot();

	int num;
	TouchGroup* ui;
};
