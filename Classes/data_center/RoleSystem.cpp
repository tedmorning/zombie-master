#include "RoleSystem.h"

void RoleSystem::init(void)
{
	//初始化角色信息
	deserializeRole();
}


void RoleSystem::deserializeRole()
{
	rapidjson::Document json;
	::readJsonFromFile("role.json", json);

	m_available_image = json["available_image"].GetString();
	m_disable_image = json["disable_image"].GetString(); 
	m_using_image = json["using_image"].GetString();
	m_usingRoleId = json["usingRoleId"].GetInt();

	const rapidjson::Value& one = json["roleInfos"];
	for(int i=0; i<k_role_type_end; i++)
	{
		m_roleInfos[i].id = one[i]["id"].GetInt();
		m_roleInfos[i].available = one[i]["available"].GetInt();
		m_roleInfos[i].name = one[i]["name"].GetString();
		m_roleInfos[i].role_chat_image = one[i]["role_chat_image"].GetString();
		m_roleInfos[i].role_image = one[i]["role_image"].GetString();
		m_roleInfos[i].desp_title = one[i]["role_desp_title"].GetString();
		m_roleInfos[i].desp_brief = one[i]["role_desp_brief"].GetString();
		m_roleInfos[i].desp_speci = one[i]["role_desp_speci"].GetString();
	}

}

void RoleSystem::serializeRole()
{

    rapidjson::Document document;
	document.SetObject();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

	rapidjson::Value array(rapidjson::kArrayType);

	for(int i=0; i<k_role_type_end; i++)
	{
		rapidjson::Value object(rapidjson::kObjectType);

		object.AddMember("id", m_roleInfos[i].id, allocator);
		object.AddMember("available", m_roleInfos[i].available, allocator);
		object.AddMember("role_chat_image", m_roleInfos[i].role_chat_image.c_str(), allocator);
		object.AddMember("role_image", m_roleInfos[i].role_image.c_str(), allocator);
		object.AddMember("role_desp_title", m_roleInfos[i].desp_title.c_str(), allocator);
		object.AddMember("role_desp_brief", m_roleInfos[i].desp_brief.c_str(), allocator);
		object.AddMember("role_desp_speci", m_roleInfos[i].desp_speci.c_str(), allocator);
		object.AddMember("name", m_roleInfos[i].name.c_str(), allocator);

		array.PushBack(object, allocator);
	}

	document.AddMember("available_image", m_available_image.c_str(), allocator);
	document.AddMember("disable_image", m_disable_image.c_str(), allocator);
	document.AddMember("using_image", m_using_image.c_str(), allocator);
	document.AddMember("usingRoleId", m_usingRoleId, allocator);

	document.AddMember("roleInfos", array, allocator);
   
	::writeJsonToFile("role.json", document);
}


const Role& RoleSystem::getCurrentRole()
{
	return m_roleInfos[m_usingRoleId - 1];
}




