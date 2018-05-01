#include "MultiTipsScene.h"
#include "BattleManage.h"

USING_NS_CC;

MultiTipsScene* MultiTipsScene::create(int tipType)
{
	MultiTipsScene *pRet = new MultiTipsScene();
	pRet -> isHasTarget = false;
	pRet -> isAutoRemove = false;
	pRet -> tipType = tipType;
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

MultiTipsScene* MultiTipsScene::create(CCPoint tagPos,bool touchRemove, int tipType)
{
	MultiTipsScene *pRet = new MultiTipsScene();
	pRet -> targetPoint = tagPos;
	pRet -> isAutoRemove = false;
	pRet -> isHasTarget = true;
	pRet -> tipType = tipType;
	pRet -> istouchRemove = touchRemove;
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

MultiTipsScene* MultiTipsScene::create(bool autoRemove, int tipType)
{
	MultiTipsScene *pRet = new MultiTipsScene();
	pRet -> isAutoRemove = autoRemove;
	pRet -> isHasTarget = false;
	pRet -> tipType = tipType;
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

bool MultiTipsScene::init()
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
		//pLayer=CCLayerColor::create(ccc4(0,0,0,200));
		/*创建剪裁节点*/
		CCClippingNode* pClip = CCClippingNode::create() ;
		pClip->setInverted(true) ;//设置是否反向，将决定画出来的区域是透明的还是黑色的。
		this->addChild(pClip) ;
	//	pLayer->setPosition(ccp(0,240));
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


	//	CCLayerColor* pLayerTwo=CCLayerColor::create(ccc4(0,0,0,200),800,240);
		/*创建剪裁节点*/
/*		CCClippingNode* pClipRect = CCClippingNode::create() ;
		pClipRect->setInverted(true) ;//设置是否反向，将决定画出来的区域是透明的还是黑色的。
		this->addChild(pClipRect) ;
		pClipRect->setPosition(ccp(0,120));
		/*注意将LayerColor层添加到剪裁节点上*/
/*		pClipRect->addChild(pLayerTwo) ;

		//创建“裁减模板”
		CCDrawNode* pStencilRect = CCDrawNode::create();
		CCPoint rectangle[4];
		rectangle[0]= ccp(0, 0);
		rectangle[1]= ccp(100,0);
		rectangle[2]= ccp(100,100);
		rectangle[3]= ccp(0, 100);
		//绘制一个矩形
		//ccColor4Fwhite = {1, 1, 1, 1};
		pStencilRect->drawPolygon(rectangle,4, red, 0, red);
		pStencilRect->setPosition(targetPoint);
		//为设置裁减节点类设置“裁减模板”
		pClipRect->setStencil(pStencilRect);
*/
	}
	else
	{
		pLayer=CCLayerColor::create(ccc4(0,0,0,100));
		this->addChild(pLayer) ;
	}

	if (isAutoRemove)
	{
		scheduleOnce(schedule_selector(MultiTipsScene::scheduleRemove),3.0f);
	}
	
	switch (tipType)
	{
	case 1:
		{
			CCSprite* tipsbg = CCSprite::create("tipbg.png");
			tipsbg -> setPosition(ccp(375,260+160));
			addChild(tipsbg);

			mTipsWord = CCLabelTTF::create("","Arial",20);
			mTipsWord -> setColor(ccYELLOW);
			mTipsWord -> setPosition(ccp(400,240+160));
			addChild(mTipsWord);

			CCSprite* pPromptShow = CCSprite::create("prompt_show.png");
			pPromptShow->setPosition(ccp(535,230+160-12));
			addChild(pPromptShow);
		//	CCActionInterval* move = CCMoveTo::create(3, ccp(pPromptShow->getPositionX(), pPromptShow->getPositionY()-12));  
			//CCActionInterval * easeBackIn = CCEaseBackIn::create(move);  

			pPromptShow->runAction(CCRepeatForever::create(CCBlink::create(1,2))); 

		}
		break;
	case 2:
		{

			CCSprite* tipsbg = CCSprite::createWithSpriteFrameName("story_3_2.png");
			tipsbg -> setPosition(ccp(150,260));
			addChild(tipsbg);

			mTipsWord = CCLabelTTF::create("","微软雅黑",34);
			//mTipsWord -> setColor(ccYELLOW);
			mTipsWord -> setPosition(ccp(450,140));
			addChild(mTipsWord,10);

			CCSprite* pPromptBg = CCSprite::createWithSpriteFrameName("role_dialog.png");
			pPromptBg -> setPosition(ccp(450,140));
			addChild(pPromptBg);

			CCSprite* pPromptShow = CCSprite::create("prompt_show.png");
			pPromptShow->setPosition(ccp(620,140-18));
			addChild(pPromptShow);
		//	CCActionInterval* move = CCMoveTo::create(3, ccp(pPromptShow->getPositionX(), pPromptShow->getPositionY()-12));  
			//CCActionInterval * easeBackIn = CCEaseBackIn::create(move);  

			pPromptShow->runAction(CCRepeatForever::create(CCBlink::create(1,2))); 
			
		}
	default:
		break;
	}
	setTouchEnabled(true);


    return true;
}

void MultiTipsScene::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1000, true);
}

void MultiTipsScene::setCallFun(cocos2d::CCCallFunc *callFunc)
{
	if (mCallFunc != NULL) {
		mCallFunc -> release();
	}
	if (callFunc != NULL) {
		mCallFunc = callFunc;
		mCallFunc -> retain();
	}
}

void MultiTipsScene::runCallBack()
{
	if (mCallFunc != NULL) {
		this -> runAction(mCallFunc);
	}
}

bool MultiTipsScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	float x = pTouch->getLocation().x;
	float y = pTouch -> getLocation().y;

	return true;
}

void MultiTipsScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//点击之后移动
	float x = pTouch->getLocation().x;
	float y = pTouch -> getLocation().y;
}

void MultiTipsScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
		//松开屏幕
	float x = pTouch->getLocation().x;
	float y = pTouch -> getLocation().y;

	if(isHasTarget)
	{
		if (ccpDistance(targetPoint,ccp(x,y)) < targetRidus || istouchRemove)
		{
			runCallBack();
			scheduleOnce(schedule_selector(MultiTipsScene::scheduleRemove),0.05);
		}
	} else 
	{
		runCallBack();
		scheduleOnce(schedule_selector(MultiTipsScene::scheduleRemove),0.05);
	}
}

void MultiTipsScene::scheduleRemove(float dt)
{
	this -> removeFromParent();
}

void MultiTipsScene::scheduleMoveCursor(float dt)
{
	this -> removeFromParent();
}

void MultiTipsScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{//如果当前为点击或移动状态，，正好来电话或者别的操作打断当前触摸事件时触发
}
