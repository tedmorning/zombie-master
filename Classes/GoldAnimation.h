#pragma once
#include "cocos2d.h"
USING_NS_CC;


class GoldAnimation : public cocos2d::CCNode
{
public:
	CREATE_FUNC(GoldAnimation);

	bool init();

	virtual void update(float delta);

	//�����ҵ�����
	void setGoldQuantity(short goldNumber);

	bool life;
private:
	//�������
	short goldQuantity;
	//���ͼƬ
	CCSprite *gold;
	//�������
	CCSprite **number;
	//������ֵĳ���
	short numberLength;
	//�Ӻ�
	CCSprite *spr;
	//Ǯ����
	CCSprite *spr2;
};