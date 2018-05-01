#include "Shopping.h"

void Shopping::init(void)
{
	//读资源文件
	deserializeShopping();
}

void Shopping::deserializeShopping()
{
	rapidjson::Document json;
	::readJsonFromFile("shopping.json", json);

	for(int i=0; i<json.Size(); i++)
	{
		m_shoppingInfos[i].catalog = json[i]["catalog"].GetInt();
		m_shoppingInfos[i].num_yuan = json[i]["num_yuan"].GetString();
		m_shoppingInfos[i].title_big = json[i]["title_big"].GetString();
		m_shoppingInfos[i].title_smalle = json[i]["title_smalle"].GetString();
		m_shoppingInfos[i].shop_description_1 = json[i]["shop_description_1"].GetString();
		m_shoppingInfos[i].shop_description_2 = json[i]["shop_description_2"].GetString();
		m_shoppingInfos[i].shop_description_3 = json[i]["shop_description_3"].GetString();
		m_shoppingInfos[i].shop_description_4 = json[i]["shop_description_4"].GetString();
	}
}

const ShoppingInfo& Shopping::getShoppingInfo(int catalog, int index)
{
	switch (catalog)
	{
	case 1:
		return m_shoppingInfos[index];
		break;
	case 2:
		return m_shoppingInfos[k_skill_end+index];
		break;
	case 3:
		return m_shoppingInfos[k_skill_end+k_role_end+index];
		break;
	default:
		break;
	}
}

