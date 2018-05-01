#ifndef  __data_center_shapping_h___
#define  __data_center_shapping_h___
#include "tool.h"

enum Shopping_Skill
{
	k_gold_recycle = 0, //��һ���
	k_more_damage,	    //�����˺�
	k_faster_speed,     //�������
	k_protected_steel,  //��������
	k_protected_magic,   //��������
	k_crash,           // ��������
	k_skill_end
};

enum Shopping_Role
{
	k_role_wolverine = 0,     //�����
	k_role_blackwidow,  //�ڹѸ�    ��������
	k_role_steelHero,   //������    ��������
	k_role_end
};

enum Shopping_Supply
{
	k_getGold = 0,           //��ý��  x10000
	k_unique_kill,            //��ñ�ɱ   x2
	k_shield,				 //��û���      x2
	k_rebirth,               //��Ѫ������ͻ���x1
	k_give_gift,			//������Ϸ�ʹ���
	k_give_big_gife,          //���������
	k_thinksgiving,			//�ж������
	k_supply_end
};

enum Shopping_catalog
{
	k_skill = 1, //����
	k_role, //��ɫ
	k_supply //����
};

//ÿһ�صļ�����Ϣ
struct ShoppingInfo
{
	int catalog; //����
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

