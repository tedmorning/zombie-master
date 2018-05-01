#include "Resource.h"

void Resource::init(void)
{
	//读资源文件
	deserializeResource();
}

void Resource::addGold(int num)
{
	m_gold+=num;
}

bool Resource::subUniqueKill()
{
	bool bRet= true;
	m_uniqueKill--;
	if(m_uniqueKill<0)
	{
		m_uniqueKill = 0;
		return false;
	}

	return bRet;
}

bool Resource::subShield()
{
	bool bRet= true;
	m_shield--;
	if(m_shield<0)
	{
		m_shield = 0;
		return false;
	}

	return bRet;
}

void Resource::addShield(int num)
{
	m_shield +=num;
}

void Resource::addUniqueKill(int num)
{
	m_uniqueKill +=num;
}

void Resource::subGold(int num)
{
	m_gold-=num;
}

unsigned int Resource::getGold()
{
	return m_gold;
}

void Resource::deserializeResource()
{
	rapidjson::Document json;
	::readJsonFromFile("resource.json", json);

	m_gold = json["gold"].GetInt();
	m_uniqueKill = json["unique_kill"].GetInt();
	m_shield = json["shield"].GetInt();
	m_gift = json["gift"].GetInt();
	
}

void Resource::save()
{
    rapidjson::Document document;
	document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	document.AddMember("gold", m_gold, allocator);
	document.AddMember("unique_kill", m_uniqueKill, allocator);
	document.AddMember("shield", m_shield, allocator);
	document.AddMember("gift", m_gift, allocator);
   
	::writeJsonToFile("resource.json", document);
}





