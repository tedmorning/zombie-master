#pragma once
#include "cocos2d.h"
#include "Firearms.h"
USING_NS_CC;

class Bullet : public CCNode
{
public:
	/* �����ӵ�
	 * type  �ӵ�����
	 * angle �ӵ�����Ƕ�
	 */
	static Bullet* create(BulletType type, float angle);

	bool init(BulletType type, float angle);

	void updata(float dt);

	void move(float xx, float yy);

	/* ���ص�ǰ�ӵ�����ײ����
	 */
	CCRect getCollisionRect();

	/* ��ǰ�ӵ�����˵���ײ���
	 */
	void checkCollision();
	void actionAfterCollsion();

	/* ���ص�ǰ�ӵ��Ĺ�����
	 */
	float getATK();

	/* ���ص�ǰ�ӵ��ĽǶ�
	 */
	float getAngle();

	/* �����ӵ�������
	 */
	int getBulletType();
private:
	//�ӵ�����
	BulletType type;

	//������
	float attack;

	//�ӵ�ͼƬ
	CCSprite* img;

	//�ӵ��Ƕ�
	float angle;

	//�ӵ��ƶ��ٶ�
	float bulletSpeed;

	// ���Ͳ
	void runFireAction();
	void setThisBulletKilled();

public:
	//�ӵ�����(true=�false=��)
	bool life;
	bool isbooming;
	BulletType bulletType;

	float boomtime;//�ӵ��ı�ըʱ��  ��ʱ���������ĵ��˶������Ѫ��
	bool iscreateForZombie;  // Ĭ�����ӵ��Ǵ�ʬ��   �����еĻ�Ҫ���Ķ�����������
	void setNotForZombie();
	void reduceHp(int hp);
	CCSprite* hpSpr;
	CCSprite* hpBgSpr;
	CCPoint destinationPoint; // ����ʬ��ʱ����ʱ��ֻ��Ӣ�۵ı���
	int hpImgWidth;
	int HP;
	int currentHp;
	int attackDistance;    // Ӣ�۱��ݵķ�Χ

	// ����ǹ��ഩ����
	int killnum;


	// �ڹѸ�  ���ǹ
	bool istouchmoved;
	void touchmove(CCPoint pos,float touchangle);
	void touchend();
	void reduceEnemyHpEveryTwoSecond(float dt);

	// ����ǹ   ����ǹ�ķ�Χ��  ����������λ���ת
	void reduceEnemyHpInRect(float dt);


	//�����ӵ�����
	void setBulletKilled(float dt);
	void reduceEnemyHPOnce(float dt);  // ��Χ��������
	void showBoom();
	void runbulletAction();
}; 