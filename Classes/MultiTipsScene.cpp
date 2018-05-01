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
	
	//����һ�����ֲ㡣
	CCLayerColor* pLayer;

	if (isHasTarget && !istouchRemove)
	{
		pLayer=CCLayerColor::create(ccc4(0,0,0,200));
		//pLayer=CCLayerColor::create(ccc4(0,0,0,200));
		/*�������ýڵ�*/
		CCClippingNode* pClip = CCClippingNode::create() ;
		pClip->setInverted(true) ;//�����Ƿ��򣬽�������������������͸���Ļ��Ǻ�ɫ�ġ�
		this->addChild(pClip) ;
	//	pLayer->setPosition(ccp(0,240));
		/*ע�⽫LayerColor����ӵ����ýڵ���*/
		pClip->addChild(pLayer) ;

		//ģ��
		CCDrawNode* pStencil = CCDrawNode::create() ;
		static ccColor4F red = {1,0,0,1} ;


		float radius = targetRidus/2 ;
		const int nCount = 200 ;
		const float angel = 2.0 * (float)M_PI/nCount ;
		static CCPoint circle[nCount] ;
		for (int i=0; i<nCount; i++) {
			float radian = i*angel ;  //����
			circle[i].x = radius * cosf(radian) ;
			circle[i].y = radius * sinf(radian) ;
		}

		pStencil->drawPolygon(circle, nCount, red, 0, red) ;
		pStencil->runAction(CCRepeatForever::create(CCSequence::createWithTwoActions(CCScaleBy::create(0.2f, 0.9f), CCScaleTo::create(0.2f, 1)))) ;

		pStencil->setPosition(targetPoint);
		pClip->setStencil(pStencil) ;  //���������Ӽ��ýڵ�����ٳ�����Stencil��ģ�����˼


	//	CCLayerColor* pLayerTwo=CCLayerColor::create(ccc4(0,0,0,200),800,240);
		/*�������ýڵ�*/
/*		CCClippingNode* pClipRect = CCClippingNode::create() ;
		pClipRect->setInverted(true) ;//�����Ƿ��򣬽�������������������͸���Ļ��Ǻ�ɫ�ġ�
		this->addChild(pClipRect) ;
		pClipRect->setPosition(ccp(0,120));
		/*ע�⽫LayerColor����ӵ����ýڵ���*/
/*		pClipRect->addChild(pLayerTwo) ;

		//�������ü�ģ�塱
		CCDrawNode* pStencilRect = CCDrawNode::create();
		CCPoint rectangle[4];
		rectangle[0]= ccp(0, 0);
		rectangle[1]= ccp(100,0);
		rectangle[2]= ccp(100,100);
		rectangle[3]= ccp(0, 100);
		//����һ������
		//ccColor4Fwhite = {1, 1, 1, 1};
		pStencilRect->drawPolygon(rectangle,4, red, 0, red);
		pStencilRect->setPosition(targetPoint);
		//Ϊ���òü��ڵ������á��ü�ģ�塱
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

			mTipsWord = CCLabelTTF::create("","΢���ź�",34);
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
	//���֮���ƶ�
	float x = pTouch->getLocation().x;
	float y = pTouch -> getLocation().y;
}

void MultiTipsScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
		//�ɿ���Ļ
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
{//�����ǰΪ������ƶ�״̬�����������绰���߱�Ĳ�����ϵ�ǰ�����¼�ʱ����
}
