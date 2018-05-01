#ifndef  __data_center_game_level_h___
#define  __data_center_game_level_h___
#include "tool.h"

//ÿһ�صļ�����Ϣ
struct LevelInfo
{
	int rating;  //����
	int stage;   //����
	int isWinOne;
//	int role_id; //��ɫ��Ϣ
	string desp; //������Ϣ
	string background;
	string title;

};

class GameLevel
{
public:
	void init(void);

	//�õ��浽�ĵ�ǰ��
	int getStage();

	//��һ��
	int addStage();

	//�õ���߹�
	int getMaxLevel();

	//�õ���ǰ�ؿ���Ϣ
	LevelInfo& getCurrentLevelInfo();

	//�õ���սģʽ��Ϣ
	LevelInfo& getForeverLevelInfo();

	//���浱ǰ�ؿ���Ϣ������
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

