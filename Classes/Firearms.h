#pragma once
#include "cocos2d.h"
#include "BattleManage.h"
#include "string"
USING_NS_CC;
using namespace std;

enum BulletType
{
	AK47, //AK47突击步枪       
	M107, //巴雷特M107重狙   1  黑寡妇
	M1014,//M1014自动霰弹枪  3
	MG4,  //德制MG4轻机枪 
	VulcanM61, //火神VulcanM61    1
	RPG_7, //铁拳RPG-7火箭    2  金刚狼
};



class Bullet;

class Firearms : public CCNode
{
public:
	CREATE_FUNC(Firearms);
	bool init();

	////初始化关卡数据
	//void initStageData();
	////解析关卡TXT文件
	//void analyTXT(unsigned char *buffer, unsigned long length);
	////加载波次时间
	//void readStageTime(unsigned char *buffer, unsigned long *index);
	////加载波次僵尸类型
	//void readStageType(unsigned char *buffer, unsigned long *index);
	////加载波次僵尸数量
	//void readStageQuantity(unsigned char *buffer, unsigned long *index);
	////加载波次路线数据
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

	void setBulletType(BulletType type,int hero); // 要根据英雄和枪的长度  调节子弹的生成位置！！
	int currentHero;

	//保存子弹
	vector<Bullet*> bulletList;
private:
	/* 创建子弹
	 * x 子弹终点X
	 * y 子弹终点Y
	 */
	void buildBullet(float x, float y,BulletType type = AK47);

	BattleManage *battle;
	//子弹发射速度(时间控制)
	float RateOfFire;
	//时间控制
	float RateOfFireTime;

	//点击的屏幕位置
	CCPoint clickPosition;
	//是否点击屏幕
	bool clickSwitch;
	bool touchbegin;
	bool touchbegin1;

	//子弹的初始发射点
	CCPoint initialPoint;
	CCPoint basePoint; // 生成子弹的基点

	//枪类型
	BulletType bullettype;


	float touchx;
	float touchy;
	void createBulletAtPos(float dt);
	void createBulletAtPos2(float dt);
	void createBullet();


	// 黑寡妇的喷火枪
	void createTouchExitBullet();  // 子弹效果触摸就一直存在
	Bullet* specialBullet;  // 特殊子弹  持续存在
	// 黑寡妇每个数秒更换子弹类型
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
	////波次
	//short wave;
	////波次时间数组
	//short *waveTime;
	////波次的僵尸类型
	//short (*waveZombieType)[WaveZombieType];
	////波次的僵尸数量
	//short (*waveZombieQuantity)[WaveZombieType];
	////每一波的路线数据
	//short(*routeData)[WaveZombieType][WaveRoute];
};