#include "Config.h"

void Config::init(void)
{
	//∂¡≈‰÷√Œƒº˛
	deserializeConfig();
}

void Config::deserializeConfig()
{
	rapidjson::Document json;
	::readJsonFromFile("config.json", json);

	m_soundVolume = json["soundVolume"].GetDouble();
}

void Config::save()
{
    rapidjson::Document document;
	document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	document.AddMember("soundVolume", m_soundVolume, allocator);
   
	::writeJsonToFile("config.json", document);
}





