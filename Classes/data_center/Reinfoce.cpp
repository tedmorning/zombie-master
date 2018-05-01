#include "Reinfoce.h"

void Reinfoce::init(void)
{
	//读强化系统运行数据
	deserializeReinfoceSys();
	//读强化系统的消费规则
	deserializeSkillCostRule();
}


void Reinfoce::deserializeReinfoceSys()
{
	rapidjson::Document json;
	::readJsonFromFile("reinfoceSystem.json", json);

	for(int i=0; i<k_reinfoceSysEnd; i++)
	{
		m_reinfoceSys[i].level = json[i]["level"].GetInt();
		m_reinfoceSys[i].maxLevel = json[i]["maxLevel"].GetInt();
		m_reinfoceSys[i].value = json[i]["value"].GetDouble();
	}
}

void Reinfoce::deserializeSkillCostRule()
{
	rapidjson::Document json;
	::readJsonFromFile("reinfoceRule.json", json);

	for(int i=0; i<k_reinfoceSysEnd; i++)
	{
		const rapidjson::Value& one = json[i];

		for(int j=0; j<k_level_End; j++)
		{
			m_skillCostRule[i].costRule[j].despAddBenefit= one[j]["desp1"].GetString();
			m_skillCostRule[i].costRule[j].despCost= one[j]["desp2"].GetString();
			m_skillCostRule[i].costRule[j].despMore = one[j]["desp3"].GetString();
			m_skillCostRule[i].costRule[j].cost = one[j]["cost"].GetInt();
			m_skillCostRule[i].costRule[j].value = one[j]["value"].GetDouble();
		}
		
	}
}

void Reinfoce::serializeReinfoceSys()
{

    rapidjson::Document document;
	document.SetArray();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	for(int i=0; i<k_reinfoceSysEnd; i++)
	{
		rapidjson::Value object(rapidjson::kObjectType);

		object.AddMember("level", m_reinfoceSys[i].level, allocator);
		object.AddMember("maxLevel", m_reinfoceSys[i].maxLevel, allocator);
		object.AddMember("value", m_reinfoceSys[i].value, allocator);

		document.PushBack(object, allocator);
	}
   
	::writeJsonToFile("reinfoceSystem.json", document);
}





