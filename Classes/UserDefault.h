// 负责存储数据

#ifndef _USER_DEFAULT_H_
#define _USER_DEFAULT_H_

#include "cocos2d.h"
#include "string.h"

USING_NS_CC;
using namespace std;

//日期
struct QDATE
{
	int year;
	int month;
	int day;
};

//获取当前日期
struct QDATE getDate();

class UserDefault : public CCObject
{
public:
	//当天是不是已经获取了奖励的金币
	static bool isGetRewardAlready();
	static void setGetRewardDate();

	//连续几天登陆
	static int getRewardDay();
	static void setRewardDay(int day);

    static void save();
};

#endif