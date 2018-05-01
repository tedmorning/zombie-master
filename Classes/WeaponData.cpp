#include "WeaponData.h"
WeaponData* WeaponData::data = NULL;

bool WeaponData::init()
{
	data = this;

	weaponAttackCount[0] = 60;
	weaponAttackCount[1] = 50;
	weaponAttackCount[2] = 40;
	weaponAttackCount[3] = 80;

	weaponAttackDuration[0] = 0.4;
	weaponAttackDuration[1] = 0.8;
	weaponAttackDuration[2] = 0.8;
	weaponAttackDuration[3] = 3.0;

	weaponAttackType[0] = WeaponAttackSingle;
	weaponAttackType[1] = WeaponAttackSingle;
	weaponAttackType[2] = WeaponAttackGroup;
	weaponAttackType[3] = WeaponAttackGroup;

	weaponAttackDis[0] = 1500;
	weaponAttackDis[1] = 1500;
	weaponAttackDis[2] = 320;
	weaponAttackDis[3] = 1500;

	return true;
}