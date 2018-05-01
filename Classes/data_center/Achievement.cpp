#include "Achievement.h"

void Achievement::init(void)
{
	//读资源文件
	deserializeAchievement();
}

void Achievement::deserializeAchievement()
{
	rapidjson::Document json;
	::readJsonFromFile("achievement.json", json);

	m_uniqueKillTimes = json["unique_kill_times"].GetInt();
	m_shieldTimes = json["shield_times"].GetInt();
	m_killedZombieNumber = json["killedZombieNumber"].GetInt();
	m_mostTopTimes = json["mostTopTimes"].GetInt();

	const rapidjson::Value& array = json["completeStatus"];

	for(int i=0; i<array.Size(); i++)
	{
		achievements[i].done = array[i]["done"].GetInt();
		achievements[i].title = array[i]["title"].GetString();
	}
	
}

void Achievement::save()
{
    rapidjson::Document document;
	document.SetObject();
	
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
		
	for (int i = 0; i < 11; i++)
	{
		rapidjson::Value obj(rapidjson::kObjectType);

		obj.AddMember("done", achievements[i].done, allocator);
		obj.AddMember("title", achievements[i].title.c_str(), allocator);

		array.PushBack(obj, allocator);
	}
	
	document.AddMember("unique_kill_times", m_uniqueKillTimes, allocator);
	document.AddMember("shield_times", m_shieldTimes, allocator);
	document.AddMember("killedZombieNumber", m_killedZombieNumber, allocator);
	document.AddMember("mostTopTimes", m_mostTopTimes, allocator);

	document.AddMember("completeStatus", array, allocator);

	::writeJsonToFile("achievement.json", document);
}

void Achievement::addShieldTimes(int num)
{
	m_shieldTimes +=num;
}

void Achievement::addUniqueKillTimes(int num)
{
	m_uniqueKillTimes +=num;
}






