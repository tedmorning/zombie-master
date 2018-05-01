#include "UserDefault.h"
#define GAME_GET_REWARD_DATE_KEY "key.game.get.reward.date"
#define GAME_REWARD_DAY "key.game.reward.day"
#define GAME_GOLD_COUNT "key.game.game.count"     // �������
#define GAME_GOLD_RECYCLE "key.game.gold.recycle"  // ��һ���
#define GAME_ADD_DAMAGE  "key.game.add.damage"   // �����˺�
#define GAME_ADD_PROTECT "key.game.add.protect"    // ��������
#define GAME_ADD_SHEILD "key.game.add.sheild"        // ��������
#define GAME_KILL_GROUP  "key.game.kill.group"        // ��������      

struct QDATE getDate()
{  
	struct QDATE dateNow;

	struct cc_timeval now;   
	CCTime::gettimeofdayCocos2d(&now, NULL);   

	struct tm *tm = NULL;  
	time_t timep = now.tv_sec;  
	tm = localtime(&timep);  
	dateNow.year = tm->tm_year + 1900;  
	dateNow.month = tm->tm_mon + 1;  
	dateNow.day = tm->tm_mday; 
	return dateNow;
} 

bool UserDefault::isGetRewardAlready()
{
	struct QDATE dateNow = getDate();
	string dateLastStr = CCUserDefault::sharedUserDefault()->getStringForKey(GAME_GET_REWARD_DATE_KEY, "");
	char buffer[512] = "";
	sprintf(buffer, "%04d%02d%02d", dateNow.year, dateNow.month, dateNow.day);
	string dateNowStr(buffer);

	return dateLastStr == dateNowStr;
}

void UserDefault::setGetRewardDate()
{
	struct QDATE dateNow = getDate();
	char buffer[512] = "";
	sprintf(buffer, "%04d%02d%02d", dateNow.year, dateNow.month, dateNow.day);
	string dateNowStr(buffer);
	CCUserDefault::sharedUserDefault()->setStringForKey(GAME_GET_REWARD_DATE_KEY, dateNowStr);
}

int UserDefault::getRewardDay()
{
	return CCUserDefault::sharedUserDefault()->getIntegerForKey(GAME_REWARD_DAY, 0);
}

void UserDefault::setRewardDay(int day)
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey(GAME_REWARD_DAY, day);
}

void UserDefault::save()
{
    CCUserDefault::sharedUserDefault() -> flush();
} 