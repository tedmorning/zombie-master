#ifndef __MULTI_TIPS_SCENE_H__
#define __MULTI_TIPS_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace  cocos2d;
using namespace cocos2d::extension;


class MultiTipsScene : public cocos2d::CCLayer
{
public:
    virtual bool init();  
	static MultiTipsScene* create(int tipType = 1);
	static MultiTipsScene* create(CCPoint tagPos,bool touchRemove = false,int isHasTip=1);
	static MultiTipsScene* create(bool autoRemove,int isHasTip=1);

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
	void scheduleMoveCursor(float dt);

	void setTipString(const char* tips)
	{
		mTipsWord -> setString(tips);
	}
private:
	CCPoint targetPoint;
	bool isHasTarget;
	bool isAutoRemove;
	int targetRidus;
	bool istouchRemove;
	int tipType;

	CCCallFunc * mCallFunc;
	CCLabelTTF* mTipsWord;
};

#endif // __HELLOWORLD_SCENE_H__
