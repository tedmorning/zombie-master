#ifndef  __data_center_resource_h___
#define  __data_center_resource_h___
#include "tool.h"

class Resource
{
public:
	void init(void);

	//增加金币
	void addGold(int num);
	//减少金币
	void subGold(int num);
	//拥有的金币
	unsigned int getGold();

	bool subUniqueKill();
	bool subShield();

	void addShield(int num=2);
	void addUniqueKill(int num=2);

	//保存到本地
	void save();

protected:
	void deserializeResource();

	CC_SYNTHESIZE(int, m_uniqueKill, UniqueKillNum);  //必杀数目
	CC_SYNTHESIZE(int, m_shield, ShieldNum);		//保护盾数目
	CC_SYNTHESIZE(int, m_gift, Gift);	
	unsigned int m_gold;

};

#endif

