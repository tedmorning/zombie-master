#pragma once
#include "cocos2d.h"
#include "BattleManage.h"
#include "string"
USING_NS_CC;
using namespace std;

enum BulletType
{
	AK47, //AK47ͻ����ǹ       
	M107, //������M107�ؾ�   1  �ڹѸ�
	M1014,//M1014�Զ�����ǹ  3
	MG4,  //����MG4���ǹ 
	VulcanM61, //����VulcanM61    1
	RPG_7, //��ȭRPG-7���    2  �����
};



class Bullet;

class Firearms : public CCNode
{
public:
	CREATE_FUNC(Firearms);
	bool init();

	////��ʼ���ؿ�����
	//void initStageData();
	////�����ؿ�TXT�ļ�
	//void analyTXT(unsigned char *buffer, unsigned long length);
	////���ز���ʱ��
	//void readStageTime(unsigned char *buffer, unsigned long *index);
	////���ز��ν�ʬ����
	//void readStageType(unsigned char *buffer, unsigned long *index);
	////���ز��ν�ʬ����
	//void readStageQuantity(unsigned char *buffer, unsigned long *index);
	////���ز���·������
	//void readStageRoute(unsigned char *buffer, unsigned long *index);

	void updata(float dt);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	inline void setBattleManage(BattleManage* bat)
	{
		battle = bat;
	}

	void setBulletType(BulletType type,int hero); // Ҫ����Ӣ�ۺ�ǹ�ĳ���  �����ӵ�������λ�ã���
	int currentHero;

	//�����ӵ�
	vector<Bullet*> bulletList;
private:
	/* �����ӵ�
	 * x �ӵ��յ�X
	 * y �ӵ��յ�Y
	 */
	void buildBullet(float x, float y,BulletType type = AK47);

	BattleManage *battle;
	//�ӵ������ٶ�(ʱ�����)
	float RateOfFire;
	//ʱ�����
	float RateOfFireTime;

	//�������Ļλ��
	CCPoint clickPosition;
	//�Ƿ�����Ļ
	bool clickSwitch;
	bool touchbegin;
	bool touchbegin1;

	//�ӵ��ĳ�ʼ�����
	CCPoint initialPoint;
	CCPoint basePoint; // �����ӵ��Ļ���

	//ǹ����
	BulletType bullettype;


	float touchx;
	float touchy;
	void createBulletAtPos(float dt);
	void createBulletAtPos2(float dt);
	void createBullet();


	// �ڹѸ������ǹ
	void createTouchExitBullet();  // �ӵ�Ч��������һֱ����
	Bullet* specialBullet;  // �����ӵ�  ��������
	// �ڹѸ�ÿ����������ӵ�����
	void changeGunType(float dt);
	void changeGunTypeBack(float dt);

	int gunheight;
	void resetInitialPoint();

	int shootBulletNum;

public:
	void createCollisionRect(int type);
	CCRect collsionRect;
	CCRect collsionRect2;
	bool hasCollsionRect;
	////����
	//short wave;
	////����ʱ������
	//short *waveTime;
	////���εĽ�ʬ����
	//short (*waveZombieType)[WaveZombieType];
	////���εĽ�ʬ����
	//short (*waveZombieQuantity)[WaveZombieType];
	////ÿһ����·������
	//short(*routeData)[WaveZombieType][WaveRoute];
};