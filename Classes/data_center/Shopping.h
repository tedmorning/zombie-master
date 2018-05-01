#ifndef  __data_center_shapping_h___
#define  __data_center_shapping_h___
#include "tool.h"

enum Shopping_Skill
{
	k_gold_recycle = 0, //金币回收
	k_more_damage,	    //附加伤害
	k_faster_speed,     //急速射击
	k_protected_steel,  //钢铁堡垒
	k_protected_magic,   //能量护盾
	k_crash,           // 死神咆哮
	k_skill_end
};

enum Shopping_Role
{
	k_role_wolverine = 0,     //金刚狼
	k_role_blackwidow,  //黑寡妇    立即解锁
	k_role_steelHero,   //钢铁侠    立即解锁
	k_role_end
};

enum Shopping_Supply
{
	k_getGold = 0,           //获得金币  x10000
	k_unique_kill,            //获得必杀   x2
	k_shield,				 //获得护盾      x2
	k_rebirth,               //满血复活，赠送护盾x1
	k_give_gift,			//激活游戏送大礼
	k_give_big_gife,          //土豪金礼包
	k_thinksgiving,			//感恩大回馈
	k_supply_end
};

enum Shopping_catalog
{
	k_skill = 1, //技能
	k_role, //角色
	k_supply //补给
};

//每一关的级别信息
struct ShoppingInfo
{
	int catalog; //分类
	string title_big;
	string title_smalle;
	string num_yuan;
	string shop_description_1;
	string shop_description_2;
	string shop_description_3;
	string shop_description_4;

};


class Shopping
{
public:
	void init(void);

	const ShoppingInfo& getShoppingInfo(int catalog, int index);

	CC_SYNTHESIZE(int, m_catalog, Catalog);
	CC_SYNTHESIZE(int, m_index, Index);
protected:
	void deserializeShopping();

	ShoppingInfo m_shoppingInfos[k_skill_end+k_supply_end+k_role_end]; 
};

#endif

