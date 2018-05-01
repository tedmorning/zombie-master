#pragma once
#include "cocos2d.h"
#include "TString.h"
#include <List>
USING_NS_CC;

//僵尸类型编号
enum ZombieType
{
	ZombieOrdinary,  //普通僵尸
	ZombieDog,    //僵尸狗
	ZombieBomb,   //炸弹僵尸
	ZombieShield, //盾牌僵尸
	ZombieSoldiers, //士兵僵尸
	ZombieDoctor, //僵尸医生
	ZombieMaster, //僵尸法师
	ZombieGiant,  //巨人僵尸
	ZombieTyrant, //爆君僵尸
	ZombieScholar,//博士僵尸
	ZombieTracker,//追踪僵尸
	ZombieGeneral,//将军僵尸
	ZombieBiochemical, //生化天使

	//  之前为像是的状态1  后面是状态2  主要针对血量和攻击力、速度的数据
	ZombieTyrantState2,
	ZombieTrackerState2,
	ZombieGeneralState2,

	ZombieCount   //僵尸种类数量
};

enum ZombieMoveState
{
	UpMove,   //往上移动
	DownMove, //往下移动
	LeftMove, //往左移动
	RightMove,//往右移动
	Situ      //原地待机
};

//僵尸动画数量(下走，左走，下攻击，左攻击，死亡)
#define ZombieAnimationQuantity 5 

#define TerminaQuantity 9 //终点数量(僵尸最终要走到哪个点)

//地图数组的行大小
#define mapCol 12
//地图数组的列大小
#define mapRow 20


/* 返回僵尸帧动画的长度
* type      僵尸类型
* actionId  僵尸动作
*/
#define ZombieFrameCount(type, actionId) EnemyData::data->getZombieFrameCount(type, actionId)
/* 返回僵尸帧动画的图片名字
* type      僵尸类型
* actionId  僵尸动作
* frameId   帧下标
*/
#define ZombieImageName(type, actionId, frameId) EnemyData::data->getZombieImageName(type, actionId, frameId)
/* 返回僵尸帧动画的名字
* type      僵尸类型
* actionId  僵尸动作
*/
#define AnimationName(type, actionId) EnemyData::data->getAnimationName(type, actionId) 

/* 返回僵尸血条偏移值
* type 僵尸类型
*/
#define HpOffset(type)  EnemyData::data->getHpOffset(type)

#define ZombieBlood(type) EnemyData::data->getZombieTotalBlood(type)
#define ZombieAttack(type) EnemyData::data->getZombieAttack(type)
#define ZombieSpeed(type) EnemyData::data->getZombieSpeed(type)
#define ZombieAttackDuration(type) EnemyData::data->getZombieAttackDuration(type)
#define ZombieWorthGold(type) EnemyData::data->getZombieWorthGold(type)

//里面保存一条完整的路线
struct RoutePoint 
{
	vector<CCPoint> pathData;
};

class EnemyData : public CCNode
{
public:
	~EnemyData();
	static EnemyData* data;
	static EnemyData* createWithID(int id,bool isrepeat = false);
	bool init();

	bool isrepeatGame;
	int repeatTimes;
	int currentLevel;
	int sceneID; // 根据场景id不同读取不同场景

	/* 返回僵尸帧动画的长度
	* type      僵尸类型
	* actionId  僵尸动作
	*/
	inline short getZombieFrameCount(ZombieType type, short actionId)
	{
		return frameCount[(short)type][actionId];
	}

	/* 返回僵尸帧动画的图片名字
	* type      僵尸类型
	* actionId  僵尸动作
	* frameId   帧下标
	*/
	inline TString getZombieImageName(ZombieType type, short actionId, short frameId)
	{
		TString str;
		if (type == ZombieOrdinary || type == ZombieBomb || type == ZombieShield|| type == ZombieMaster || type == ZombieTyrant || type == ZombieTyrantState2
			|| type == ZombieDoctor || type == ZombieSoldiers || type == ZombieDog || type == ZombieScholar|| type == ZombieTracker || type == ZombieTrackerState2
			|| type == ZombieGiant || type == ZombieGeneral || type == ZombieGeneralState2 || type == ZombieBiochemical)
		{
			if (actionId == 4 && (type == ZombieShield || type == ZombieMaster || type == ZombieDoctor || type == ZombieSoldiers || type == ZombieDog || type == ZombieScholar|| type == ZombieTracker 
				|| type == ZombieTrackerState2 || type == ZombieGiant || type == ZombieGeneral || type == ZombieGeneralState2))  // 盾牌僵尸死亡
			{
				str += 1;
			}
			else
				str += (type + 1);    // 动画还没有！！！   
		}
		else
		{
			//type = ZombieOrdinary;
			str += 1;
		}
		
		switch (actionId)
		{
		case 0: //往下走
			str += "_DownWalk_";
			break;
		case 1: //往左走
			str += "_LeftWalk_";
			break;
		case 2: //往下攻击
			str += "_DownAttack_";
			break;
		case 3: //往左攻击
			str += "_LeftAttack_";
			break;
		case 4: //死亡动作
			str += "_death_";
			break;
		}
		str += frameId;
		str += ".png";
		return str;
	}

	/* 返回僵尸帧动画的名字
	* type      僵尸类型
	* actionId  僵尸动作
	*/
	inline TString getAnimationName(ZombieType type, short actionId)
	{
		TString str;
		if (type == ZombieOrdinary || type == ZombieBomb || type == ZombieShield|| type == ZombieMaster || type == ZombieTyrant || type == ZombieTyrantState2
			|| type == ZombieDoctor || type == ZombieSoldiers || type == ZombieDog || type == ZombieScholar|| type == ZombieTracker || type == ZombieTrackerState2
			|| type == ZombieGiant  || type == ZombieGeneral || type == ZombieGeneralState2 || type == ZombieBiochemical)
		{
			if (actionId == 4 && (type == ZombieShield || type == ZombieMaster || type == ZombieDoctor || type == ZombieSoldiers || type == ZombieDog
				|| type == ZombieScholar|| type == ZombieTracker || type == ZombieTrackerState2|| type == ZombieGiant
				|| type == ZombieGeneral || type == ZombieGeneralState2))  // 盾牌僵尸死亡
			{
				str += 1;
			}
			else
				str += (type + 1);    // 动画还没有！！！   
		}
		else
			str += 1;
		str += "_Zombie_";
		str += actionId;

		return str;
	}

	/* 返回此僵尸是否能远程攻击
	 * type  僵尸类型
	 */
	bool isZombieRemote(ZombieType type);

	//地图数组
	short mapData[mapCol][mapRow];

	//地图路线的数量
	short routeQuantity;

	//本关所有路径，，全部保存在这里，，
	RoutePoint(*allRoute)[TerminaQuantity];

	//每关出僵尸的出口(每关出口不固定,保存每个出口的位置，以地图下标为准)
	vector<CCPoint> routeStartPoint;

	//获得路径
	RoutePoint *getRoute(short routeId);

	/* 返回僵尸血条偏移值
	 * type 僵尸类型
	 */
	inline CCPoint getHpOffset(ZombieType type)
	{
		return zombieHpOffset[type];
	}

	inline int getZombieTotalBlood(ZombieType type)
	{
		if (!isrepeatGame)
		{
			return zombieBloodCount[type] * (1 + sumZombieCount[currentLevel]);
		}
		else
			return zombieBloodCount[type] * (1 + repeatTimes/20.0);
	}
	inline int getZombieAttack(ZombieType type)
	{
		if (!isrepeatGame)
		{
			return zombieAttackCount[type] * (1 + sumZombieCount[currentLevel]);
		}
		else
			return zombieAttackCount[type] * (1 + repeatTimes/20.0);
	}
	inline float getZombieSpeed(ZombieType type)
	{
		if (!isrepeatGame)
		{
			return zombieMoveSpeed[type] * (1 + sumZombieCount[currentLevel]);
		}
		else
			return zombieMoveSpeed[type] * (1 + repeatTimes/20.0) ;
	}
	inline float getZombieAttackDuration(ZombieType type)
	{
		return zombieAttackDuration[type];
	}
	inline int getZombieWorthGold(ZombieType type)
	{
		return zombieWorthGold[type];
	}
	//随机返回一个终点位置
	CCPoint getTerminalPoint();

private:

	//解析关卡TXT文件
	void analyTXT();

	//计算出所有的路径
	void countAllRoute();
	void countRoute(short routeIndex, vector<CCPoint> *pathData);
	

	//僵尸每个动作的帧长度
	short frameCount[ZombieCount][ZombieAnimationQuantity];

	//僵尸血条的偏移值
	CCPoint zombieHpOffset[ZombieCount];

	//终点位置
	CCPoint terminalPoint[9];

	
	// 僵尸血量
	int zombieBloodCount[ZombieCount];
	// 僵尸攻击力
	int zombieAttackCount[ZombieCount];
	// 攻击间隔
	int zombieAttackDuration[ZombieCount];
	// 僵尸速度
	float zombieMoveSpeed[ZombieCount];
	// 僵尸价格
	int zombieWorthGold[ZombieCount];

	// 僵尸属性提升
	float sumZombieCount[ZombieCount];
};


class PathNode
{
public:
	PathNode(short col, short row);
	~PathNode();

	//移动步数与估值相加
	short F;
	//从起点位置移到到当前位置所走的步数
	short G;
	//从当前点到终点的估算路径
	short H;

	short col; //行
	short row; //列

	//父节点的指针
	PathNode *father;

	inline short getF()
	{
		return F;
	}

	void setPos(short co, short ro);

	void set(short g, short h);

	void setFather(PathNode *fath);
};

class Cmpare
{
public:
	bool operator()(const PathNode *st1, const PathNode  *st2) const;
};