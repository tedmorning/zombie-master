// װ������

#ifndef __WEAPON_DATA_H__
#define __WEAPON_DATA_H__

#include "cocos2d.h"
#include "string.h"

USING_NS_CC;
using namespace std;


typedef enum WeaponType
{
	WeaponTypeFireGod,            //������
	WeaponTypeLaserCannon,     //������
	WeaponTypeShotGun,           //ɢ��ǹ
	WeaponTypeMissile,             //����/���Ͳ

	WeaponCount
};

typedef enum WeaponAttackType
{
	WeaponAttackSingle,          // ����
	WeaponAttackGroup           // ��Χ
};

class WeaponData : public CCNode
{
public:
	static WeaponData* data;
	CREATE_FUNC(WeaponData);
	bool init();

	// װ��������
	int weaponAttackCount[WeaponCount];
	// װ���������
	float weaponAttackDuration[WeaponCount];
	// ��������   ���巶Χ
	WeaponAttackType weaponAttackType[WeaponCount];
	// ��������
	int weaponAttackDis[WeaponCount];
};

#endif