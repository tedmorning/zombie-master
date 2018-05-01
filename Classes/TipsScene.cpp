#include "TipsScene.h"
#include "BattleManage.h"

USING_NS_CC;

TipsScene* TipsScene::create()
{
	TipsScene *pRet = new TipsScene();
	pRet -> isHasTarget = false;
	pRet -> isAutoRemove = false;
	pRet -> shouldPauseGame = true;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

TipsScene* TipsScene::create(CCPoint tagPos,bool touchRemove)
{
	TipsScene *pRet = new TipsScene();
	pRet -> targetPoint = tagPos;
	pRet -> isAutoRemove = false;
	pRet -> isHasTarget = true;
	pRet -> istouchRemove = touchRemove;
	pRet -> shouldPauseGame = true;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;

	}
}

TipsScene* TipsScene::create(bool autoRemove,bool shouldpause)
{
	TipsScene *pRet = new TipsScene();
	pRet -> isAutoRemove = autoRemove;
	pRet -> isHasTarget = false;
	pRet -> shouldPauseGame = shouldpause;
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

bool TipsScene::init()
{
    if ( !CCLayer::init())
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	mCallFunc = NULL;
	targetRidus = 100;
	
	//创建一个遮罩层。
	CCLayerColor* pLayer;

	if (isHasTarget && !istouchRemove)
	{
		pLayer=CCLayerColor::create(ccc4(0,0,0,200));

		/*创建剪裁节点*/
		CCClippingNode* pClip = CCClippingNode::create() ;
		pClip->setInverted(true) ;//设置是否反向，将决定画出来的区域是透明的还是黑色的。
		this->addChild(pClip) ;
		/*注意将LayerColor层添加到剪裁节点上*/
		pClip->addChild(pLayer) ;

		//模板
		CCDrawNode* pStencil = CCDrawNode::create() ;
		static ccColor4F red = {1,0,0,1} ;


		float radius = targetRidus/2 ;
		const int nCount = 200 ;
		const float angel = 2.0 * (float)M_PI/nCount ;
		static CCPoint circle[nCount] ;
		for (int i=0; i<nCount; i++) {
			float radian = i*angel ;  //弧度
			circle[i].x = radius * cosf(radian) ;
			circle[i].y = radius * sinf(radian) ;
		}

		pStencil->drawPolygon(circle, nCount, red, 0, red) ;
		pStencil->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleBy::create(0.2f, 0.9f), CCScaleTo::create(0.2f, 1)))) ;

		pStencil->setPosition(targetPoint);
		pClip->setStencil(pStencil) ;  //将这个区域从剪裁节点上面抠出来。Stencil是模板的意思
	}
	else if (shouldPauseGame)
	{
		pLayer=CCLayerColor::create(ccc4(0,0,0,100));
		this->addChild(pLayer) ;
	}
	else
	{
	}

	if (isAutoRemove)
	{
		scheduleOnce(schedule_selector(TipsScene::scheduleResumeGame),2.8);
		scheduleOnce(schedule_selector(TipsScene::scheduleRemove),3.0f);
	}
	
	CCSprite* tipsbg = CCSprite::create("tipbg.png");
	//tipsbg -> setPosition(ccp(375,260));
	tipsbg -> setPosition(ccp(375,260 + 160));
	addChild(tipsbg);

	mTipsWord = CCLabelTTF::create("","Arial",20);
	mTipsWord -> setColor(ccYELLOW);
	//mTipsWord -> setPosition(ccp(400,240));
	mTipsWord -> setPosition(ccp(400,240 + 160));
	addChild(mTipsWord);
	setTouchEnabled(true);

	if (shouldPauseGame)
	{
		BattleManage* pauseLayer = BattleManage::oneself;
		pauseLayer -> pauseSchedulerAndActions();
	}

    return true;
}

void TipsScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1000, shouldPauseGame);
}

void TipsScene::setCallFun(cocos2d::CCCallFunc *callFunc)
{
	if (mCallFunc != NULL) {
		mCallFunc -> release();
	}
	if (callFunc != NULL) {
		mCallFunc = callFunc;
		mCallFunc -> retain();
	}
}

void TipsScene::runCallBack()
{
	if (mCallFunc != NULL) {
		this -> runAction(mCallFunc);
	}
}

bool TipsScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	float x = pTouch->getLocation().x;
	float y = pTouch -> getLocation().y;

	return true;
}

void TipsScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//点击之后移动
	float x = pTouch->getLocation().x;
	float y = pTouch -> getLocation().y;
}

void TipsScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	//松开屏幕
	float x = pTouch->getLocation().x;
	float y = pTouch -> getLocation().y;

	if (!isAutoRemove)
	{
		if (isHasTarget)
		{
			if (ccpDistance(targetPoint,ccp(x,y)) < targetRidus || istouchRemove)
			{
				BattleManage* pauseLayer = BattleManage::oneself;
				pauseLayer -> resumeSchedulerAndActions();
				runCallBack();
				scheduleOnce(schedule_selector(TipsScene::scheduleRemove),0.05);
			}
		}
		else	
		{
			BattleManage* pauseLayer = BattleManage::oneself;
			pauseLayer -> pauseSchedulerAndActions();
			this -> removeFromParent();
		}
	}
}

void TipsScene::scheduleRemove(float dt)
{
	this -> removeFromParent();
}

void TipsScene::scheduleResumeGame(float dt)
{
	BattleManage* pauseLayer = BattleManage::oneself;
	pauseLayer -> resumeSchedulerAndActions();
}

void TipsScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{//如果当前为点击或移动状态，，正好来电话或者别的操作打断当前触摸事件时触发
}
