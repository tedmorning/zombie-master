#include "GameLevel.h"

void GameLevel::init(void)
{
	//读资源文件
	deserializeGameLevel();
}

int GameLevel::getStage()
{
	return m_stage;
}

int GameLevel::addStage()
{
	if(m_maxLevel != m_stage)
	{
		m_stage +=  1;
	}
	return m_stage;
}


void GameLevel::addLevelInfo(LevelInfo levelInfo)
{
	m_levelInfos.push_back(levelInfo);
}

void GameLevel::deserializeGameLevel()
{
	rapidjson::Document json;
	::readJsonFromFile("gameLevel.json", json);

	rapidjson::Document jLevelInfos;
	::readJsonFromFile("levelInfos.json", jLevelInfos);

	m_stage = json["stage"].GetInt();
	m_maxLevel = json["maxLevel"].GetInt();
	m_isWinOne = json["isWinOne"].GetInt();

	const rapidjson::Value& one = json["levelInfos"];
	CCLOG("%i " ,one.Size());

	for(int i=0; i<one.Size(); i++)
	{
		LevelInfo li;
		li.rating = one[i]["rating"].GetInt();
	//	li.role_id = one[i]["role_id"].GetInt();
		li.desp = jLevelInfos[i]["desp"].GetString();
		li.background = jLevelInfos[i]["background"].GetString();
		li.title = jLevelInfos[i]["title"].GetString();

		addLevelInfo(li);
	}

	//无尽关卡信息
	int endIndex = jLevelInfos.Size()-1;
	LevelInfo li;
	li.rating = 0;
	li.desp = jLevelInfos[endIndex]["desp"].GetString();
	li.background = jLevelInfos[endIndex]["background"].GetString();
	li.title = jLevelInfos[endIndex]["title"].GetString();

	addLevelInfo(li);
}

LevelInfo& GameLevel::getCurrentLevelInfo()
{
	return m_levelInfos.at(m_stage - 1);
}

LevelInfo& GameLevel::getForeverLevelInfo()
{
	int size = m_levelInfos.size();
	return m_levelInfos.at(size-1);
}
int GameLevel::getMaxLevel()
{
	return m_maxLevel;
}

void GameLevel::saveLevelInfo()
{

    rapidjson::Document document;
	document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	document.AddMember("stage", m_stage, allocator);
	document.AddMember("maxLevel", m_maxLevel, allocator);
	document.AddMember("isWinOne", m_isWinOne, allocator);

	rapidjson::Value array(rapidjson::kArrayType);

	for(int i =0; i< m_levelInfos.size() - 1; i++)
	{
		LevelInfo li = m_levelInfos.at(i);
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("rating", li.rating, allocator);

		array.PushBack(object, allocator);
	}

	document.AddMember("levelInfos", array, allocator);
	

	::writeJsonToFile("gameLevel.json", document);
}





