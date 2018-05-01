#ifndef  __data_center_game_level_h___
#define  __data_center_game_level_h___
#include "tool.h"

//每一关的级别信息
struct LevelInfo
{
	int rating;  //评级
	int stage;   //几关
	int isWinOne;
//	int role_id; //角色信息
	string desp; //描述信息
	string background;
	string title;

};

class GameLevel
{
public:
	void init(void);

	//得到玩到的当前关
	int getStage();

	//下一关
	int addStage();

	//得到最高关
	int getMaxLevel();

	//得到当前关卡信息
	LevelInfo& getCurrentLevelInfo();

	//得到挑战模式信息
	LevelInfo& getForeverLevelInfo();

	//保存当前关卡信息到本地
	void saveLevelInfo();

	CC_SYNTHESIZE(int, m_isWinOne, IsWinOne);

	std::vector<LevelInfo> m_levelInfos; 
protected:
	void deserializeGameLevel();
	void addLevelInfo(LevelInfo levelInfo);

	int m_stage;
	int m_maxLevel;
};

#endif

