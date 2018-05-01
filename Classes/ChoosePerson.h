#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "RoleShow.h"

USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;



class ChoosePerson :
	public cocos2d::CCLayer
{
public:
	ChoosePerson();

	virtual bool init();
	static cocos2d::CCScene* scene();
	void buttonClicked(CCObject *pSender, TouchEventType eType);
	void onEnter();

	void failCallback();
	CREATE_FUNC(ChoosePerson);

	void showFocus(int tag);
	void cascadeShow(int tag);
	void setFocusTag(int tag){ focusTag = tag; };
private:

	void initRoleInfo();
	void initRoleAnimation();
	
	
	void buyRole(int tag);

	void lockBlink(float dt);

	TouchGroup* ui;
	RoleShow* m_pRoleShow;
	int focusTag;

	std::function<void()>  m_successCallback;
	std::function<void()> m_failCallback;

};
