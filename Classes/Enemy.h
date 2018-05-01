#pragma once
#include "cocos2d.h"
#include "BattleManage.h"
#include "EnemyData.h"
#include "string"
USING_NS_CC;
using namespace std;

enum ZombieState
{
	Walk,   //����״̬
	Attack, //����״̬
	Cure,    // ����״̬
	Call,     // �ٻ�״̬
	Move,   // ˲��״̬
	Death,  //����״̬
};

enum ZombieAttackType
{
	Normal_Attack,
	Boom_Attack
};

class Bullet;

class Enemy : public cocos2d::CCNode
{
public:
	Enemy();
	~Enemy();

	static Enemy* create(BattleManage *battle);
	bool init(BattleManage *battle);
	void updata(float dt);

	//����Ѫ��ͼƬ
	void updataHpSprite();

	/* ��Ѫ
	 * value ���ٵ�Ѫ��
	 */
	void reduceHp(float value);

	void setHP(float value);

	/* ������ʬ
	 * type    ��ʬ����
	 * routeId ��ʬ·��
	 */
	void buildZombie(short type, short routeId);

	/* ����Ѫ��ͼƬ
	 */
	void buildHpImage(bool created = false);

	/* ���ص�ǰ�ӵ�����ײ����
	*/
	CCRect getCollisionRect();

	/* ��ײ���
	 * rect   ��ײ�ľ��ο�
	 * bullet �ӵ�����
	 * return �����ײ���ˣ��ͷ���true�����򷵻�false
	 */
	bool checkCollision(CCRect rect, Bullet* bullet);

	void setPositions(CCPoint point);
	
	void move(float x, float y);

	//�����Ĵ���
	void deathHandle();

	void runAttackAction();
	void showSpecialAttackAction();
	void showSpecialAttackActionDelay(float dt);

	int getCurBlood(){return currentHP;}
public:
	//����(true=��, false=��)
	bool life;
	//״̬
	ZombieState state;
private:
	//��������
	void buildAnimation();

	//������ʬ��������
	void buildDeathAnimation();

	//�ƶ���ʬ
	void moveZombie();

	//��鵱ǰ����λ�ã��ı��ƶ�״̬
	void changeMoveState();

	//�ı佩ʬ����
	void changeAnimation();

	//������һ��Ҫ�ƶ���λ��
	void setNextPoint();

	//����·��
	RoutePoint *pathData;
	//��ǰ�ƶ���·��������ĸ�λ����
	short pathIndex;
	//��һ�����λ��
	CCPoint nextPoint;

	BattleManage* battle;

	//��ʬ�ƶ��ٶ�
	float moveSpeed;

	//��ʬ����
	ZombieType zombieType;

	//���鶯������0.������  1.������  2.���¹���  3.���ҹ���
	CCSprite* spriteAnimation[ZombieAnimationQuantity];
	CCAnimate* animate[ZombieAnimationQuantity];

	//Զ�̹�������
	CCSprite* remoteAttack;

	//��ʬ��ǰ�ƶ�����(���ı��ƶ�)
	ZombieMoveState moveOrien;
	ZombieMoveState moveOrienPre;  //��ͣǰ���ƶ�����

	//�յ�λ��
	CCPoint endPoint;


	//Ѫ����ͼƬ
	CCSprite* hpSpr;
	CCSprite* hpBgSpr;
	//ͼƬ�Ŀ�
	short hpImgWidth;
	//Ѫ����ƫ��λ��
	short offsetX;
	short offsetY;

	//���Ѫ��
	int HP;
	//��ǰѪ��
	int currentHP;
	
	//��ǰ��ʬ��·���±�
	short routeIndex;
	//��ǰ�����ĸ�·�����ĸ����ƶ�
	short movePointIndex;
	//��ʬ��ǰ�Ķ����±�
	short currentActionIndex;
	//��ʬ��һ���������±�(-1��ʾ��ǰһ������)
	short lastActionIndex;

	// ����ֵ���������������������
	int m_attack_count;
	float m_attack_duration;
	int m_current_worth_gold;

	// ��ʬ�ļ��� attack״̬���ͷ�
	void startCureZombie(float dt);
	void cureOtherZombie(float dt);         // ����
	void stopCureOtherZombie(float dt);  // ֹͣ����
	void callOtherZombie(float dt);          // �ٻ�
	void callOtherZombieOver(float dt);
	void stopCallZombie(float dt);
	void showMomentMoveAction();  // ����˲�ƶ���  ���ŵ�һ���ʱ���ƶ�����
	void momentMoveZombie(float dt);    // ˲���ƶ�
	void resetZombieWalk(float dt); // �ͷ��꼼��֮�������

	//��ʬҽ��
	bool isFirstAttacked;

	// ����������Ч
	bool iscuring;
	void showCureAnimation(float dt);
	// ˲�ƶ���
	void showMoveAnimation();
	// �ٻ�����
	void showCallAnimation();
	void removeSprite(CCObject* pSender);
public:
	CCPoint getNextPoint(){return nextPoint;}
	void setNextPoint(CCPoint next){nextPoint.x = next.x;nextPoint.y = next.y;}
	int getPathIndex(){return pathIndex;}
	void setPathIndex(int index){pathIndex = index;}
	ZombieMoveState getMoveState(){return moveOrien;}
	void setMoveState(ZombieMoveState state){moveOrien = state;}
	short getRouteIndex(){return routeIndex;}
	void setRouteIndex(short index){routeIndex = index;}
	void setRouteData(RoutePoint* data){pathData = data;}
	RoutePoint* getRouteData(){return pathData;}
	void rebuildAnimation();

	void removeChildByObject(CCObject* pSender);
	void removeChildOnly(CCObject* pSender);  // �������Ƴ�child

	// �Ƿ񱻴�͸
	bool isBulletThrough;

	// ���ƹ������
	float duration;
}; 
