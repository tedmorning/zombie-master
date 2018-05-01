#ifndef __TIPS_SCENE_H__
#define __TIPS_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace  cocos2d;
using namespace cocos2d::extension;


class TipsScene : public cocos2d::CCLayer
{
public:
    virtual bool init();  
	static TipsScene* create();
	static TipsScene* create(CCPoint tagPos,bool touchRemove = false);
	static TipsScene* create(bool autoRemove,bool shouldpause = true);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual void registerWithTouchDispatcher();

	// 设置回调
	void setCallFun(CCCallFunc * callFunc);

	// 运行回调
	void runCallBack();

	void scheduleRemove(float dt);
	void scheduleResumeGame(float dt);

	void setTipString(const char* tips)
	{
		mTipsWord -> setString(tips);
	}

	bool shouldPauseGame;
private:
	CCPoint targetPoint;
	bool isHasTarget;
	bool isAutoRemove;
	int targetRidus;
	bool istouchRemove;

	CCCallFunc * mCallFunc;
	CCLabelTTF* mTipsWord;
};

#endif // __HELLOWORLD_SCENE_H__
