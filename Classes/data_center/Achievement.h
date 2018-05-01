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
	//���浽����
	void save();
	void addShieldTimes(int num = 1);
	void addUniqueKillTimes(int num = 1);

	AchievementDetail achievements[11];

protected:
	void deserializeAchievement();

	CC_SYNTHESIZE(int, m_uniqueKillTimes, UniqueKillNumTimes);  //��ɱʹ�ô���
	CC_SYNTHESIZE(int, m_shieldTimes, ShieldNumTimes);		//������ʹ�ô���
	CC_SYNTHESIZE(int, m_killedZombieNumber, KilledZombieNumber);	//ɱ����ʬ����
	CC_SYNTHESIZE(int, m_mostTopTimes, MostTopTimes);	//��ʷ���ͨ������
};

#endif

