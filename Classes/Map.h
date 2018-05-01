#pragma once
#include "cocos2d.h"
#include "BattleManage.h"
USING_NS_CC;

//����ͼƬ������
#define WANG_LENGTH 7

class Map : public cocos2d::CCNode
{
public:
	Map();
	~Map();

	static Map* create(BattleManage *battle);

	bool init(BattleManage *battle);

	//��ʼ����ͼ����
	void initMap1();
	//������
	void initMap2();
	//������
	void initMap3();

	void updata(float dt);

	//���������ɫ
	void setWang();
private:
	BattleManage *battle;
	//������ʱ����ʱ����
	float wangTimeAxis;
	//��������
	CCSprite* wang[WANG_LENGTH];
};