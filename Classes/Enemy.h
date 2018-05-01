#pragma once
#include "cocos2d.h"
#include "BattleManage.h"
#include "EnemyData.h"
#include "string"
USING_NS_CC;
using namespace std;

enum ZombieState
{
	Walk,   //行走状态
	Attack, //攻击状态
	Cure,    // 治疗状态
	Call,     // 召唤状态
	Move,   // 瞬移状态
	Death,  //死亡状态
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

	//更新血条图片
	void updataHpSprite();

	/* 掉血
	 * value 减少的血量
	 */
	void reduceHp(float value);

	void setHP(float value);

	/* 创建僵尸
	 * type    僵尸类型
	 * routeId 僵尸路线
	 */
	void buildZombie(short type, short routeId);

	/* 创建血条图片
	 */
	void buildHpImage(bool created = false);

	/* 返回当前子弹的碰撞矩形
	*/
	CCRect getCollisionRect();

	/* 碰撞检测
	 * rect   碰撞的矩形框
	 * bullet 子弹对象
	 * return 如果碰撞到了，就返回true，否则返回false
	 */
	bool checkCollision(CCRect rect, Bullet* bullet);

	void setPositions(CCPoint point);
	
	void move(float x, float y);

	//死亡的处理
	void deathHandle();

	void runAttackAction();
	void showSpecialAttackAction();
	void showSpecialAttackActionDelay(float dt);

	int getCurBlood(){return currentHP;}
public:
	//生命(true=活, false=死)
	bool life;
	//状态
	ZombieState state;
private:
	//创建动画
	void buildAnimation();

	//创建僵尸死亡动画
	void buildDeathAnimation();

	//移动僵尸
	void moveZombie();

	//检查当前动画位置，改变移动状态
	void changeMoveState();

	//改变僵尸动画
	void changeAnimation();

	//设置下一个要移动的位置
	void setNextPoint();

	//保存路径
	RoutePoint *pathData;
	//当前移动到路径上面的哪个位置了
	short pathIndex;
	//下一个点的位置
	CCPoint nextPoint;

	BattleManage* battle;

	//僵尸移动速度
	float moveSpeed;

	//僵尸类型
	ZombieType zombieType;

	//精灵动画对像0.往下跑  1.左右跑  2.往下攻击  3.左右攻击
	CCSprite* spriteAnimation[ZombieAnimationQuantity];
	CCAnimate* animate[ZombieAnimationQuantity];

	//远程攻击动画
	CCSprite* remoteAttack;

	//僵尸当前移动方向(往哪边移动)
	ZombieMoveState moveOrien;
	ZombieMoveState moveOrienPre;  //暂停前的移动方向

	//终点位置
	CCPoint endPoint;


	//血条的图片
	CCSprite* hpSpr;
	CCSprite* hpBgSpr;
	//图片的宽
	short hpImgWidth;
	//血条的偏移位置
	short offsetX;
	short offsetY;

	//最大血量
	int HP;
	//当前血量
	int currentHP;
	
	//当前僵尸的路线下标
	short routeIndex;
	//当前正往哪个路线上哪个点移动
	short movePointIndex;
	//僵尸当前的动画下标
	short currentActionIndex;
	//僵尸上一个动画的下标(-1表示无前一个动画)
	short lastActionIndex;

	// 攻击值、攻击间隔、死亡掉落金币
	int m_attack_count;
	float m_attack_duration;
	int m_current_worth_gold;

	// 僵尸的技能 attack状态下释放
	void startCureZombie(float dt);
	void cureOtherZombie(float dt);         // 治疗
	void stopCureOtherZombie(float dt);  // 停止治疗
	void callOtherZombie(float dt);          // 召唤
	void callOtherZombieOver(float dt);
	void stopCallZombie(float dt);
	void showMomentMoveAction();  // 播放瞬移动画  播放到一半的时候移动距离
	void momentMoveZombie(float dt);    // 瞬间移动
	void resetZombieWalk(float dt); // 释放完技能之后继续走

	//僵尸医生
	bool isFirstAttacked;

	// 播放治疗特效
	bool iscuring;
	void showCureAnimation(float dt);
	// 瞬移动画
	void showMoveAnimation();
	// 召唤动画
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
	void removeChildOnly(CCObject* pSender);  // 仅仅是移除child

	// 是否被穿透
	bool isBulletThrough;

	// 控制攻击间隔
	float duration;
}; 
