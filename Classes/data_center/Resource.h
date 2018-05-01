#ifndef  __data_center_resource_h___
#define  __data_center_resource_h___
#include "tool.h"

class Resource
{
public:
	void init(void);

	//���ӽ��
	void addGold(int num);
	//���ٽ��
	void subGold(int num);
	//ӵ�еĽ��
	unsigned int getGold();

	bool subUniqueKill();
	bool subShield();

	void addShield(int num=2);
	void addUniqueKill(int num=2);

	//���浽����
	void save();

protected:
	void deserializeResource();

	CC_SYNTHESIZE(int, m_uniqueKill, UniqueKillNum);  //��ɱ��Ŀ
	CC_SYNTHESIZE(int, m_shield, ShieldNum);		//��������Ŀ
	CC_SYNTHESIZE(int, m_gift, Gift);	
	unsigned int m_gold;

};

#endif

