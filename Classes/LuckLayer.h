#ifndef _LUCKLAYER_H_
#define _LUCKLAYER_H_
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;
class LuckLayer:public CCLayer
{
public:
	LuckLayer();
	~LuckLayer();

	CREATE_FUNC(LuckLayer);
	bool init();
	ImageView * m_items[6];
	ImageView * m_light;

	void onSureClick(CCObject *obj,TouchEventType eventType);

	void onBackClick(CCObject *obj, TouchEventType eventType);

	void payCallBack(bool res);

	void startTurn();

	void update(float dt);

	int m_awardIndex;
	float m_interval;
	float m_totalTime;
	UILabel * m_label;
	bool m_isFirstLucy;
};

#endif