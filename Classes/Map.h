#pragma once
#include "cocos2d.h"
#include "BattleManage.h"
USING_NS_CC;

//网子图片的数量
#define WANG_LENGTH 7

class Map : public cocos2d::CCNode
{
public:
	Map();
	~Map();

	static Map* create(BattleManage *battle);

	bool init(BattleManage *battle);

	//初始化地图背景
	void initMap1();
	//背景二
	void initMap2();
	//背景三
	void initMap3();

	void updata(float dt);

	//设置网变红色
	void setWang();
private:
	BattleManage *battle;
	//网被打时变红的时间轴
	float wangTimeAxis;
	//七种网子
	CCSprite* wang[WANG_LENGTH];
};