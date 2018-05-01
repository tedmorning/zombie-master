#pragma once
#include "cocos2d.h"
#include "BattleManage.h"
#include "vector"
#include "Enemy.h"
USING_NS_CC;
using namespace std;


//僵尸节点，控制出来节奏
struct ZombieNode
{
	//僵尸出来的时间
	float time;
	//此节点出的僵尸种类
	ZombieType type;
	//僵尸路线
	short routeId;
};

//每波僵尸最多出现几种不同僵尸
#define WaveZombieType 3
//最大路线数
#define WaveRoute 7

class EnemyManage : public CCNode
{
public:
	EnemyManage();
	~EnemyManage();

	static EnemyManage* create(BattleManage *bat,int level,bool isrepeat);

	static EnemyManage* oneself;

	bool init(BattleManage *bat);

	void updata(float dt);

	void updateZombieZorder(float dt);

	/* 创建僵尸
	 * dt 时间（每一帧的时间）
	 */
	void buildZombie(float dt);

	/* 检测子弹与敌人是否碰撞
	 * rect   子弹的矩形框
	 * bullet 子弹对象
	 * return 如果碰撞到了，就返回true，否则返回false
	 */
	bool bulletAndEnemyCollision(CCRect rect, Bullet* bullet);

	void reduceEnemyHpInDistance(CCPoint pos,int distance,float hurt);

	/* 返回所有敌人的vector对象
	 */
	inline vector<Enemy*> getEnemyList()
	{
		return enemyList;
	}
    
    inline int getEnemySize(){return enemyList.size();}
    bool buildZombieFinished;

	// 0729
	void cureZombieInDistance(CCPoint pos,int dis = 100,int cureCount = 2); // 以当前僵尸为圆心dis距离恢复僵尸cureCount血量

	void showCallAnimation(Enemy* zombie);
	void removeCallAnimation(CCObject* pSender);
	void buildCalledZombie(Enemy* zombie);  // 根据僵尸信息创建召唤僵尸
private:
	BattleManage* battle;

	int currentLevel;// 当前关卡数

	//创建僵尸的时间轴
	float buildZombieTimeAxis;

	//所有的敌人都存放在这
	vector<Enemy*> enemyList;
	//存储范围影响的敌人  僵尸技能或者英雄技能
	vector<Enemy*> enemyEffectGroup;
	//僵尸的波数
	short quantity;

	/////////////////////读取僵尸出来规则数据////////////////////////////////
	//初始化关卡数据
	void initStageData();
	//解析关卡TXT文件
	void analyTXT(unsigned char *buffer, unsigned long length);
	//加载波次时间
	void readStageTime(unsigned char *buffer, unsigned long *index);
	//加载波次僵尸类型
	void readStageType(unsigned char *buffer, unsigned long *index);
	//加载波次僵尸数量
	void readStageQuantity(unsigned char *buffer, unsigned long *index);
	//加载波次路线数据
	void readStageRoute(unsigned char *buffer, unsigned long *index);

	//跟据数组来判断是否创建僵尸
	void buildZombie(short waveType, short *waveQuantity, short *waveRouteIndex, bool *waveFinish);

	/* 获得当前要刷到屏幕中的僵尸路线
	 * waveType 此波中的哪种僵尸（每波最多三种僵尸）
	 * waveRouteID 此波中的路线
	*/
	short getStatuZombieRoute(short waveType, short *waveRouteID);

	//波次
	int wave;
	//波次时间数组
	short *waveTime;
	//波次的僵尸类型
	short(*waveZombieType)[WaveZombieType];
	//波次的僵尸数量
	short(*waveZombieQuantity)[WaveZombieType];
	//每一波的路线数据
	short(*routeData)[WaveZombieType][WaveRoute];

	//当前已经出到第几波了
	int waveIndex;
	//记录当前这波僵尸, 第一种出了几个兵
	short waveQuantity1;
	//记录这一波里面僵尸的路线(根据从第一个口到最后一个口循环出)
	short waveRouteIndex1;
	//判断这一波里面的第一种僵尸是否出完
	bool waveFinish1;
	//第二种
	short waveQuantity2;
	short waveRouteIndex2;
	bool waveFinish2;
	//第三种
	short waveQuantity3;
	short waveRouteIndex3;
	bool waveFinish3;

	bool istest;

	//
	int zombieZorder;
	bool isrepeatGame;
	int repeatTimes;
	float repeatCountTime;
	void reLoadData();
public:
	void reduceEnemyHPAngleAndDis(float angle,float dis,float hurt);
	void reduceEnemyHpInRect(float angle,float dis,float hurt);
};