#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;


class GameMainMenu :
	public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene(bool isBegin);

	void buttonClicked(CCObject *pSender, TouchEventType eType);
	void musicChanged(CCObject *pSender, TouchEventType eType) ;

	static GameMainMenu* create(bool isBegin);

	bool m_IsTip;

	virtual void onEnter();
private:
	void sceneTransitionEffect();
	void sceneTransition();
	void fadeoutOneTip(float dt);
	void fadeoutButton(float dt);
	void showTip(float dt);
	void initVolume();
	void setButtonVisible(bool visible);
	
	void rotationRight(float dt);
	void rotationLeft(float dt);
	void scheduleRotationLeft();
	void scheduleRotationRight();
	void showMenu(float dt);
	void showButtonAndRoation(float dt);
	void scheduleShowButtonAndRoation();
	void setButtonVisibleTrue(float dt);
	void stopRotation(float dt);
	void letinvisible(float dt);
	void moveToRight(CCNode* pSender);
	void moveToLeft(CCNode* pSender);

	CCPoint left;
	CCPoint right;
	int m_tag;
	bool isBegin;

	int opacityTip;
	int opacityTipTwo;

	float leftRotation;
	float rightRotation;

	float rotationOffset;

	TouchGroup* ui;
	std::function<void()> m_successCallback;
	std::function<void()> m_failCallback;
	CCSprite* pEffectSprite ;

};

