#include "GiftLayer.h"
#include "JniCommon.h"
#include "data_center//RunningData.h"

CCRenderTexture* getScreenCapture(bool updateScreen)
{
	CCRenderTexture* s_pRenderTexture=NULL;
	if (updateScreen)
	{
		CC_SAFE_RELEASE_NULL(s_pRenderTexture);
		s_pRenderTexture = CCRenderTexture::create(800, 480);
		s_pRenderTexture->retain();
		s_pRenderTexture->begin();
		CCDirector::sharedDirector()->getRunningScene()->visit();
		s_pRenderTexture->end();
	}
	return s_pRenderTexture;
}

GiftLayer::GiftLayer()
{
	m_isScene = false;
}


GiftLayer::~GiftLayer()
{
}

CCScene* GiftLayer::scene(GiftLayer* layer)
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease objec

	CCSprite* pBackground = CCSprite::createWithTexture(getScreenCapture(true)->getSprite()->getTexture());
	pBackground->setPosition(ccp(400.0, 240.0));
	pBackground->setFlipY(true);
	scene->addChild(pBackground);
	// add layer as a child to scene
	scene->addChild(layer);
	layer->m_isScene = true;
	// return the scene
	return scene;
}
GiftLayer* GiftLayer::create(PayType payType)
{
	GiftLayer *ref = new GiftLayer();
	ref->init(payType);
	ref->autorelease();

	return ref;
}

bool GiftLayer::init(PayType payType)
{
	CCLayer::init();
	m_payType = payType;

	CCLayerColor * layer = CCLayerColor::create(ccc4(0,0,0,200));

	addChild(layer);

	m_pUiLayer = TouchGroup::create();
	addChild(m_pUiLayer);
	Layout* m_pPanel = NULL;
	
	moveIn(this);
// 	m_successFun = NULL;
// 	m_failFun = NULL;
	if (payType == k_pay_newgift)
	{
		m_pPanel=dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("giftlayer/newgifLayer.json"));
	}
	
	if (payType == k_pay_supergift)
	{
		m_pPanel = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("giftlayer/supergifLayer.json"));
	}


	if (payType == k_pay_revievegift)
	{
		m_pPanel = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("giftlayer/revivegifLayer.json"));
	}


	if (payType == k_pay_logingif || payType == k_pay_logingif_free)
	{
		m_pPanel = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("giftlayer/logingifLayer.json"));
		UILabel * label = NULL;
		if (payType == k_pay_logingif_free)
		{
			label = dynamic_cast<UILabel*>(m_pPanel->getChildByName("freelabel"));
			label->setVisible(true);
			
			UIImageView * content = dynamic_cast<UIImageView*>(m_pPanel->getChildByName("content"));
			content->loadTexture("freelogin.png");

		}
			
		if (payType == k_pay_logingif)
		{
			label = dynamic_cast<UILabel*>(m_pPanel->getChildByName("label"));
			label->setVisible(true);
		}
			


	}


	if (payType == k_pay_exit)
	{
		m_pPanel = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("giftlayer/exitgift.json"));
	}


// 	if (payType == VIP)
// 	{
// 		m_pPanel = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("giftlayer/vipLayer.json"));
// 	}

	m_pUiLayer->addWidget(m_pPanel);

	UIButton * button = dynamic_cast<UIButton*>(m_pPanel->getChildByName("button"));

	button->addTouchEventListener(this, SEL_TouchEvent(&GiftLayer::onButtonClick));


	UIButton * colse = dynamic_cast<UIButton*>(m_pPanel->getChildByName("close"));

	colse->addTouchEventListener(this, SEL_TouchEvent(&GiftLayer::onClose));

	m_hasSuccessFun = false;
	m_hasfailFun = false;
	return true;
}

void GiftLayer::onButtonClick(CCObject * obj, TouchEventType eventType)
{
	if (eventType == TOUCH_EVENT_ENDED)
	{
		if (m_payType == k_pay_logingif_free)
		{
			callSuccess(m_payType);
		}
		else if (m_payType == k_pay_exit)
		{
			payCode(k_pay_logingif, this, Sel_Pay_Event(&GiftLayer::payCallBack));
		}
		else
		{
			payCode((int)m_payType, this, Sel_Pay_Event(&GiftLayer::payCallBack));
		}
		
	}
}

void GiftLayer::onClose(CCObject * obj, TouchEventType eventType)
{
	if (eventType == TOUCH_EVENT_ENDED)
	{
		if (m_failFun&&m_hasfailFun)
			this->m_failFun();

		if (m_payType==k_pay_exit)
		{
			::exitGame();
		}
		else
		{
			if (m_isScene)
				CCDirector::sharedDirector()->popScene();
			else
				removeFromParentAndCleanup(true);
		}
		


	}
}
void GiftLayer::setSuccessCallFun(std::function<void()> sfun)
{
	m_successFun = sfun;
	m_hasSuccessFun = true;
}

void GiftLayer::setFailCallFun(std::function<void()> sfun)
{
	m_failFun =sfun ;
	m_hasfailFun = true;
}

void GiftLayer::payCallBack(bool result)
{
	if (result)
	{
		this->scheduleOnce(SEL_SCHEDULE(&GiftLayer::callSuccess),0.01);
	}
	else
	{
		this->m_failFun();
		removeFromParent();
	}
	
}

void GiftLayer::onExit()
{
	CCLayer::onExit();
}

void GiftLayer::callSuccess(float dt)
{
	if (m_successFun&&m_hasSuccessFun)
	{
		this->m_successFun();
	}

	if (m_payType == k_pay_exit)
	{
		exitGame();
	}

	RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
	Resource& resource = RunningData::getInstance()->getResource();
	if (m_payType == k_pay_newgift)
	{
		Role& role = rs.m_roleInfos[k_blackwidow];
		role.available = 1; //角色可用
		rs.serializeRole(); //保存到本地

		resource.addShield(5);
		resource.save(); //保存

	}
	else if (m_payType == k_pay_supergift)
	{

		Role& role = rs.m_roleInfos[k_ironmen];
		role.available = 1; //角色可用
		rs.serializeRole(); //保存到本地


		resource.addUniqueKill(5);
		resource.save(); //保存
	}
	else if (m_payType == k_pay_revievegift)
	{


	}
	else if (m_payType == k_pay_logingif)
	{
		
		resource.addUniqueKill(8);
		resource.addShield(8);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("fuhuo", CCUserDefault::sharedUserDefault()->getIntegerForKey("fuhuo", 0) + 2);
		resource.save();
	
	}
	else if (m_payType == k_pay_logingif_free)
	{
		resource.addUniqueKill(1);
		resource.addShield(1);
		CCUserDefault::sharedUserDefault()->setIntegerForKey("fuhuo", CCUserDefault::sharedUserDefault()->getIntegerForKey("fuhuo", 0) + 2);
		resource.save();
	}

	if (m_isScene)
		CCDirector::sharedDirector()->popScene();
	else
		removeFromParentAndCleanup(true);
}





