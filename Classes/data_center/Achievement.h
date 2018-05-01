#ifndef  __data_center_achievement_h___
#define  __data_center_achievemnet_h___
#include "tool.h"

struct AchievementDetail
{
	int done;
	string title;
};


class Achievement
{
public:
	void init(void);
	//保存到本地
	void save();
	void addShieldTimes(int num = 1);
	void addUniqueKillTimes(int num = 1);

	AchievementDetail achievements[11];

protected:
	void deserializeAchievement();

	CC_SYNTHESIZE(int, m_uniqueKillTimes, UniqueKillNumTimes);  //必杀使用次数
	CC_SYNTHESIZE(int, m_shieldTimes, ShieldNumTimes);		//保护盾使用次数
	CC_SYNTHESIZE(int, m_killedZombieNumber, KilledZombieNumber);	//杀死僵尸总数
	CC_SYNTHESIZE(int, m_mostTopTimes, MostTopTimes);	//历史最高通过波次
};

#endif

