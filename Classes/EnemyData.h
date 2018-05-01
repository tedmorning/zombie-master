#pragma once
#include "cocos2d.h"
#include "TString.h"
#include <List>
USING_NS_CC;

//��ʬ���ͱ��
enum ZombieType
{
	ZombieOrdinary,  //��ͨ��ʬ
	ZombieDog,    //��ʬ��
	ZombieBomb,   //ը����ʬ
	ZombieShield, //���ƽ�ʬ
	ZombieSoldiers, //ʿ����ʬ
	ZombieDoctor, //��ʬҽ��
	ZombieMaster, //��ʬ��ʦ
	ZombieGiant,  //���˽�ʬ
	ZombieTyrant, //������ʬ
	ZombieScholar,//��ʿ��ʬ
	ZombieTracker,//׷�ٽ�ʬ
	ZombieGeneral,//������ʬ
	ZombieBiochemical, //������ʹ

	//  ֮ǰΪ���ǵ�״̬1  ������״̬2  ��Ҫ���Ѫ���͹��������ٶȵ�����
	ZombieTyrantState2,
	ZombieTrackerState2,
	ZombieGeneralState2,

	ZombieCount   //��ʬ��������
};

enum ZombieMoveState
{
	UpMove,   //�����ƶ�
	DownMove, //�����ƶ�
	LeftMove, //�����ƶ�
	RightMove,//�����ƶ�
	Situ      //ԭ�ش���
};

//��ʬ��������(���ߣ����ߣ��¹������󹥻�������)
#define ZombieAnimationQuantity 5 

#define TerminaQuantity 9 //�յ�����(��ʬ����Ҫ�ߵ��ĸ���)

//��ͼ������д�С
#define mapCol 12
//��ͼ������д�С
#define mapRow 20


/* ���ؽ�ʬ֡�����ĳ���
* type      ��ʬ����
* actionId  ��ʬ����
*/
#define ZombieFrameCount(type, actionId) EnemyData::data->getZombieFrameCount(type, actionId)
/* ���ؽ�ʬ֡������ͼƬ����
* type      ��ʬ����
* actionId  ��ʬ����
* frameId   ֡�±�
*/
#define ZombieImageName(type, actionId, frameId) EnemyData::data->getZombieImageName(type, actionId, frameId)
/* ���ؽ�ʬ֡����������
* type      ��ʬ����
* actionId  ��ʬ����
*/
#define AnimationName(type, actionId) EnemyData::data->getAnimationName(type, actionId) 

/* ���ؽ�ʬѪ��ƫ��ֵ
* type ��ʬ����
*/
#define HpOffset(type)  EnemyData::data->getHpOffset(type)

#define ZombieBlood(type) EnemyData::data->getZombieTotalBlood(type)
#define ZombieAttack(type) EnemyData::data->getZombieAttack(type)
#define ZombieSpeed(type) EnemyData::data->getZombieSpeed(type)
#define ZombieAttackDuration(type) EnemyData::data->getZombieAttackDuration(type)
#define ZombieWorthGold(type) EnemyData::data->getZombieWorthGold(type)

//���汣��һ��������·��
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
	int sceneID; // ���ݳ���id��ͬ��ȡ��ͬ����

	/* ���ؽ�ʬ֡�����ĳ���
	* type      ��ʬ����
	* actionId  ��ʬ����
	*/
	inline short getZombieFrameCount(ZombieType type, short actionId)
	{
		return frameCount[(short)type][actionId];
	}

	/* ���ؽ�ʬ֡������ͼƬ����
	* type      ��ʬ����
	* actionId  ��ʬ����
	* frameId   ֡�±�
	*/
	inline TString getZombieImageName(ZombieType type, short actionId, short frameId)
	{
		TString str;
		if (type == ZombieOrdinary || type == ZombieBomb || type == ZombieShield|| type == ZombieMaster || type == ZombieTyrant || type == ZombieTyrantState2
			|| type == ZombieDoctor || type == ZombieSoldiers || type == ZombieDog || type == ZombieScholar|| type == ZombieTracker || type == ZombieTrackerState2
			|| type == ZombieGiant || type == ZombieGeneral || type == ZombieGeneralState2 || type == ZombieBiochemical)
		{
			if (actionId == 4 && (type == ZombieShield || type == ZombieMaster || type == ZombieDoctor || type == ZombieSoldiers || type == ZombieDog || type == ZombieScholar|| type == ZombieTracker 
				|| type == ZombieTrackerState2 || type == ZombieGiant || type == ZombieGeneral || type == ZombieGeneralState2))  // ���ƽ�ʬ����
			{
				str += 1;
			}
			else
				str += (type + 1);    // ������û�У�����   
		}
		else
		{
			//type = ZombieOrdinary;
			str += 1;
		}
		
		switch (actionId)
		{
		case 0: //������
			str += "_DownWalk_";
			break;
		case 1: //������
			str += "_LeftWalk_";
			break;
		case 2: //���¹���
			str += "_DownAttack_";
			break;
		case 3: //���󹥻�
			str += "_LeftAttack_";
			break;
		case 4: //��������
			str += "_death_";
			break;
		}
		str += frameId;
		str += ".png";
		return str;
	}

	/* ���ؽ�ʬ֡����������
	* type      ��ʬ����
	* actionId  ��ʬ����
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
				|| type == ZombieGeneral || type == ZombieGeneralState2))  // ���ƽ�ʬ����
			{
				str += 1;
			}
			else
				str += (type + 1);    // ������û�У�����   
		}
		else
			str += 1;
		str += "_Zombie_";
		str += actionId;

		return str;
	}

	/* ���ش˽�ʬ�Ƿ���Զ�̹���
	 * type  ��ʬ����
	 */
	bool isZombieRemote(ZombieType type);

	//��ͼ����
	short mapData[mapCol][mapRow];

	//��ͼ·�ߵ�����
	short routeQuantity;

	//��������·������ȫ�������������
	RoutePoint(*allRoute)[TerminaQuantity];

	//ÿ�س���ʬ�ĳ���(ÿ�س��ڲ��̶�,����ÿ�����ڵ�λ�ã��Ե�ͼ�±�Ϊ׼)
	vector<CCPoint> routeStartPoint;

	//���·��
	RoutePoint *getRoute(short routeId);

	/* ���ؽ�ʬѪ��ƫ��ֵ
	 * type ��ʬ����
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
	//�������һ���յ�λ��
	CCPoint getTerminalPoint();

private:

	//�����ؿ�TXT�ļ�
	void analyTXT();

	//��������е�·��
	void countAllRoute();
	void countRoute(short routeIndex, vector<CCPoint> *pathData);
	

	//��ʬÿ��������֡����
	short frameCount[ZombieCount][ZombieAnimationQuantity];

	//��ʬѪ����ƫ��ֵ
	CCPoint zombieHpOffset[ZombieCount];

	//�յ�λ��
	CCPoint terminalPoint[9];

	
	// ��ʬѪ��
	int zombieBloodCount[ZombieCount];
	// ��ʬ������
	int zombieAttackCount[ZombieCount];
	// �������
	int zombieAttackDuration[ZombieCount];
	// ��ʬ�ٶ�
	float zombieMoveSpeed[ZombieCount];
	// ��ʬ�۸�
	int zombieWorthGold[ZombieCount];

	// ��ʬ��������
	float sumZombieCount[ZombieCount];
};


class PathNode
{
public:
	PathNode(short col, short row);
	~PathNode();

	//�ƶ��������ֵ���
	short F;
	//�����λ���Ƶ�����ǰλ�����ߵĲ���
	short G;
	//�ӵ�ǰ�㵽�յ�Ĺ���·��
	short H;

	short col; //��
	short row; //��

	//���ڵ��ָ��
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