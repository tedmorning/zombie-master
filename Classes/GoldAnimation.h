#pragma once
#include "cocos2d.h"
USING_NS_CC;


class GoldAnimation : public cocos2d::CCNode
{
public:
	CREATE_FUNC(GoldAnimation);

	bool init();

	virtual void update(float delta);

	//传入金币的数字
	void setGoldQuantity(short goldNumber);

	bool life;
private:
	//金币数量
	short goldQuantity;
	//金币图片
	CCSprite *gold;
	//金币数字
	CCSprite **number;
	//金币数字的长度
	short numberLength;
	//加号
	CCSprite *spr;
	//钱符号
	CCSprite *spr2;
};