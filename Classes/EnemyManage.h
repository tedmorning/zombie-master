#pragma once
#include "cocos2d.h"
#include "BattleManage.h"
#include "vector"
#include "Enemy.h"
USING_NS_CC;
using namespace std;


//��ʬ�ڵ㣬���Ƴ�������
struct ZombieNode
{
	//��ʬ������ʱ��
	float time;
	//�˽ڵ���Ľ�ʬ����
	ZombieType type;
	//��ʬ·��
	short routeId;
};

//ÿ����ʬ�����ּ��ֲ�ͬ��ʬ
#define WaveZombieType 3
//���·����
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

	/* ������ʬ
	 * dt ʱ�䣨ÿһ֡��ʱ�䣩
	 */
	void buildZombie(float dt);

	/* ����ӵ�������Ƿ���ײ
	 * rect   �ӵ��ľ��ο�
	 * bullet �ӵ�����
	 * return �����ײ���ˣ��ͷ���true�����򷵻�false
	 */
	bool bulletAndEnemyCollision(CCRect rect, Bullet* bullet);

	void reduceEnemyHpInDistance(CCPoint pos,int distance,float hurt);

	/* �������е��˵�vector����
	 */
	inline vector<Enemy*> getEnemyList()
	{
		return enemyList;
	}
    
    inline int getEnemySize(){return enemyList.size();}
    bool buildZombieFinished;

	// 0729
	void cureZombieInDistance(CCPoint pos,int dis = 100,int cureCount = 2); // �Ե�ǰ��ʬΪԲ��dis����ָ���ʬcureCountѪ��

	void showCallAnimation(Enemy* zombie);
	void removeCallAnimation(CCObject* pSender);
	void buildCalledZombie(Enemy* zombie);  // ���ݽ�ʬ��Ϣ�����ٻ���ʬ
private:
	BattleManage* battle;

	int currentLevel;// ��ǰ�ؿ���

	//������ʬ��ʱ����
	float buildZombieTimeAxis;

	//���еĵ��˶��������
	vector<Enemy*> enemyList;
	//�洢��ΧӰ��ĵ���  ��ʬ���ܻ���Ӣ�ۼ���
	vector<Enemy*> enemyEffectGroup;
	//��ʬ�Ĳ���
	short quantity;

	/////////////////////��ȡ��ʬ������������////////////////////////////////
	//��ʼ���ؿ�����
	void initStageData();
	//�����ؿ�TXT�ļ�
	void analyTXT(unsigned char *buffer, unsigned long length);
	//���ز���ʱ��
	void readStageTime(unsigned char *buffer, unsigned long *index);
	//���ز��ν�ʬ����
	void readStageType(unsigned char *buffer, unsigned long *index);
	//���ز��ν�ʬ����
	void readStageQuantity(unsigned char *buffer, unsigned long *index);
	//���ز���·������
	void readStageRoute(unsigned char *buffer, unsigned long *index);

	//�����������ж��Ƿ񴴽���ʬ
	void buildZombie(short waveType, short *waveQuantity, short *waveRouteIndex, bool *waveFinish);

	/* ��õ�ǰҪˢ����Ļ�еĽ�ʬ·��
	 * waveType �˲��е����ֽ�ʬ��ÿ��������ֽ�ʬ��
	 * waveRouteID �˲��е�·��
	*/
	short getStatuZombieRoute(short waveType, short *waveRouteID);

	//����
	int wave;
	//����ʱ������
	short *waveTime;
	//���εĽ�ʬ����
	short(*waveZombieType)[WaveZombieType];
	//���εĽ�ʬ����
	short(*waveZombieQuantity)[WaveZombieType];
	//ÿһ����·������
	short(*routeData)[WaveZombieType][WaveRoute];

	//��ǰ�Ѿ������ڼ�����
	int waveIndex;
	//��¼��ǰ�Ⲩ��ʬ, ��һ�ֳ��˼�����
	short waveQuantity1;
	//��¼��һ�����潩ʬ��·��(���ݴӵ�һ���ڵ����һ����ѭ����)
	short waveRouteIndex1;
	//�ж���һ������ĵ�һ�ֽ�ʬ�Ƿ����
	bool waveFinish1;
	//�ڶ���
	short waveQuantity2;
	short waveRouteIndex2;
	bool waveFinish2;
	//������
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