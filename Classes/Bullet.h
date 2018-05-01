#pragma once
#include "cocos2d.h"
#include "Firearms.h"
USING_NS_CC;

class Bullet : public CCNode
{
public:
	/* 创建子弹
	 * type  子弹类型
	 * angle 子弹发射角度
	 */
	static Bullet* create(BulletType type, float angle);

	bool init(BulletType type, float angle);

	void updata(float dt);

	void move(float xx, float yy);

	/* 返回当前子弹的碰撞矩形
	 */
	CCRect getCollisionRect();

	/* 当前子弹与敌人的碰撞检测
	 */
	void checkCollision();
	void actionAfterCollsion();

	/* 返回当前子弹的攻击力
	 */
	float getATK();

	/* 返回当前子弹的角度
	 */
	float getAngle();

	/* 返回子弹的类型
	 */
	int getBulletType();
private:
	//子弹类型
	BulletType type;

	//攻击力
	float attack;

	//子弹图片
	CCSprite* img;

	//子弹角度
	float angle;

	//子弹移动速度
	float bulletSpeed;

	// 喷火筒
	void runFireAction();
	void setThisBulletKilled();

public:
	//子弹生命(true=活，false=死)
	bool life;
	bool isbooming;
	BulletType bulletType;

	float boomtime;//子弹的爆炸时间  该时间内碰到的敌人都会减少血量
	bool iscreateForZombie;  // 默认下子弹是打僵尸的   但是有的还要打别的东西。。。。
	void setNotForZombie();
	void reduceHp(int hp);
	CCSprite* hpSpr;
	CCSprite* hpBgSpr;
	CCPoint destinationPoint; // 不打僵尸的时候，暂时是只打英雄的堡垒
	int hpImgWidth;
	int HP;
	int currentHp;
	int attackDistance;    // 英雄堡垒的范围

	// 激光枪最多穿三个
	int killnum;


	// 黑寡妇  喷火枪
	bool istouchmoved;
	void touchmove(CCPoint pos,float touchangle);
	void touchend();
	void reduceEnemyHpEveryTwoSecond(float dt);

	// 激光枪   激光枪的范围里  但是这个矩形会旋转
	void reduceEnemyHpInRect(float dt);


	//设置子弹死亡
	void setBulletKilled(float dt);
	void reduceEnemyHPOnce(float dt);  // 范围攻击！！
	void showBoom();
	void runbulletAction();
}; 