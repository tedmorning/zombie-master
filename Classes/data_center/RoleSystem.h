#ifndef  __ROLE_SYSTEM_h___
#define  __ROLE_SYSTEM_h___
#include "tool.h"

enum RoleType
{ 
	k_wolverine=0,	    //½ð¸ÕÀÇ
	k_blackwidow,		//ºÚ¹Ñ¸¾
	k_ironmen,			//¸ÖÌúÏÀ
	k_role_type_end
};

struct Role
{
	int id;
	int available;
	string name;
	string role_chat_image;
	string role_image;
	string desp_title;
	string desp_brief;
	string desp_speci;
};


class RoleSystem
{
public:
	void init(void);

	void serializeRole();

	Role m_roleInfos[k_role_type_end];

	const Role& getCurrentRole();

protected:
	void deserializeRole();
	
	CC_SYNTHESIZE(int, m_usingRoleId, UsingRoleId);
	CC_SYNTHESIZE_READONLY(string, m_using_image, UsingImage);
	CC_SYNTHESIZE_READONLY(string, m_available_image, AvailableImage);
	CC_SYNTHESIZE_READONLY(string, m_disable_image, DisableImage);

};

#endif

