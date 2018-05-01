#ifndef  __REINFOCE_h___
#define  __REINFOCE_h___
#include "tool.h"

enum ReinfoceSysKind
{
	k_jibihuishou = 0,
	k_fujiashanghai,
	k_jisusheji,
	k_gangtiebaolei,
	k_nenglianghudun,
	k_sishenpaoxiao,
	k_reinfoceSysEnd
};

enum Level
{
	k_level_1 = 0,
	k_level_2,
	k_level_3,
	k_level_4,
	k_level_5,
	k_level_max,
	k_level_End
};

struct ReinfoceSys
{
	int level;
	int maxLevel;
	float value;
};

struct CostRule
{
	int cost;
	float value;
	std::string despAddBenefit;
	std::string despCost;
	std::string despMore;
};

struct SkillCostRule
{
	CostRule costRule[k_level_End];
};


class Reinfoce
{
public:
	void init(void);

	void serializeReinfoceSys();

	ReinfoceSys m_reinfoceSys[k_reinfoceSysEnd];
	SkillCostRule m_skillCostRule[k_reinfoceSysEnd];

protected:
	void deserializeReinfoceSys();
	void deserializeSkillCostRule();

};

#endif

