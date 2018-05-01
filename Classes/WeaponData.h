// 装备数据

#ifndef __WEAPON_DATA_H__
#define __WEAPON_DATA_H__

#include "cocos2d.h"
#include "string.h"

USING_NS_CC;
using namespace std;


typedef enum WeaponType
{
	WeaponTypeFireGod,            //火神炮
	WeaponTypeLaserCannon,     //激光炮
	WeaponTypeShotGun,           //散弹枪
	WeaponTypeMissile,             //导弹/火箭筒

	WeaponCount
};

typedef enum WeaponAttackType
{
	WeaponAttackSingle,          // 单体
	WeaponAttackGroup           // 范围
};

class WeaponData : public CCNode
{
public:
	static WeaponData* data;
	CREATE_FUNC(WeaponData);
	bool init();

	// 装备攻击力
	int weaponAttackCount[WeaponCount];
	// 装备攻击间隔
	float weaponAttackDuration[WeaponCount];
	// 攻击类型   单体范围
	WeaponAttackType weaponAttackType[WeaponCount];
	// 攻击距离
	int weaponAttackDis[WeaponCount];
};

#endif