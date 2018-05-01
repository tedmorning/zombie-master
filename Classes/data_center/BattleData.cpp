#include "BattleData.h"

void BattleData::init(void)
{
	//����Դ�ļ�
	deserializeBattleData();
}


void BattleData::deserializeBattleData()
{
	rapidjson::Document json;
	::readJsonFromFile("battle.json", json);
	for(int i=0; i<json.Size(); i++)
	{
		battlePrompt[i].id = json[i]["id"].GetInt();
		battlePrompt[i].title = json[i]["title"].GetString();
	}
}




