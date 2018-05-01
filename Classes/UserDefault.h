// ����洢����

#ifndef _USER_DEFAULT_H_
#define _USER_DEFAULT_H_

#include "cocos2d.h"
#include "string.h"

USING_NS_CC;
using namespace std;

//����
struct QDATE
{
	int year;
	int month;
	int day;
};

//��ȡ��ǰ����
struct QDATE getDate();

class UserDefault : public CCObject
{
public:
	//�����ǲ����Ѿ���ȡ�˽����Ľ��
	static bool isGetRewardAlready();
	static void setGetRewardDate();

	//���������½
	static int getRewardDay();
	static void setRewardDay(int day);

    static void save();
};

#endif