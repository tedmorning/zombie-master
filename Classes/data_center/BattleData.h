#ifndef  __data_center_battle_data_h___
#define  __data_center_battle_data_h___
#include "tool.h"

//每一关的级别信息
struct BattlePromptInfo
{
	int id;
	string title;

};

class BattleData
{
public:
	void init(void);

	BattlePromptInfo battlePrompt[12];

protected:

	void deserializeBattleData();

};

#endif

