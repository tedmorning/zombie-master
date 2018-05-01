#include "LuckLayer.h"
#include "JniCommon.h"
#include "data_center/RunningData.h"
LuckLayer::LuckLayer()
{
}


LuckLayer::~LuckLayer()
{
}

bool LuckLayer::init()
{

	CCLayer::init();
	TouchGroup* m_pUiLayer = TouchGroup::create();
//	UILayer *m_pUiLayer = UILayer::create();
	addChild(m_pUiLayer);
	m_isFirstLucy = CCUserDefault::sharedUserDefault()->getBoolForKey("firstlucky",true);





	Layout* m_pPanel = dynamic_cast<Layout*>(GUIReader::shareReader()->widgetFromJsonFile("giftlayer/choujiang.json"));

	m_pUiLayer->addWidget(m_pPanel);

	UIImageView * item = dynamic_cast<UIImageView*> (m_pPanel->getChildByName("item"));

	for (int i = 0; i < 6;i++)
	{
		char name[40];

		sprintf(name,"item%02d",i+1);
		m_items[i] = dynamic_cast<UIImageView*>(item->getChildByName(name));

	}

	UIImageView * back = dynamic_cast<UIImageView*>(m_pPanel->getChildByName("back"));
	UIImageView * sure = dynamic_cast<UIImageView*>(m_pPanel->getChildByName("sure"));
	back->setVisible(false);
	m_label = dynamic_cast<UILabel*>(m_pPanel->getChildByName("tip"));
	m_light = dynamic_cast<UIImageView*>(m_pPanel->getChildByName("light"));

	m_label->setText(_text("tip"));
	back->addTouchEventListener(this, SEL_TouchEvent(&LuckLayer::onBackClick));
	sure->addTouchEventListener(this, SEL_TouchEvent(&LuckLayer::onSureClick));
	m_awardIndex = -1;

	m_interval = 0.0;
	m_totalTime = 5.0;
	return true;
}

void LuckLayer::onBackClick(CCObject *obj, TouchEventType eventType)
{
	if (eventType == TOUCH_EVENT_ENDED)
	{
		removeFromParent();
	}

}

void LuckLayer::onSureClick(CCObject *obj, TouchEventType eventType)
{
	if (eventType == TOUCH_EVENT_ENDED)
	{
		
		if (m_awardIndex == -1)
		{
			//startTurn();
			m_totalTime = 2+(rand()%3);
			this->scheduleUpdate();
		}
		else
		{
			payCode(k_pay_award, this, Sel_Pay_Event(&LuckLayer::payCallBack));
		}

	}
}

void LuckLayer::startTurn()
{

}

void LuckLayer::payCallBack(bool res)
{
	if (res)
	{
		Resource& resource = RunningData::getInstance()->getResource();
		switch (m_awardIndex)
		{
		case 0://gold 5w
			resource.addGold(50000);
			break;
		case 1://护盾 5
			resource.addShield(15);
			break;
		case 2://必杀 5
			resource.addUniqueKill(15);
			break;
		case 3://gold 10w
			resource.addGold(100000);
			break;
		case 4://护盾 10
			resource.addShield(30);
			break;
		case 5://必杀 10
			resource.addUniqueKill(30);
			break;
		default:
			break;
		}
		resource.save();
	}

	removeFromParent();
}

void LuckLayer::update(float dt)
{
	m_interval += dt;
	m_totalTime -= dt;
	if (m_interval > 0.1)
	{
		m_interval = 0;
		m_awardIndex = (m_awardIndex + 1) % 6;
		
		m_light->setPosition(m_items[m_awardIndex]->getParent()->convertToWorldSpace(m_items[m_awardIndex]->getPosition()));

		if (m_totalTime <= 0)
		{
			if (m_awardIndex < 3)
				m_awardIndex += 3;

			if (m_isFirstLucy)
			{
				CCUserDefault::sharedUserDefault()->setBoolForKey("firstlucky",false);
				m_awardIndex = 5;
			}
			m_light->setPosition(m_items[m_awardIndex]->getParent()->convertToWorldSpace(m_items[m_awardIndex]->getPosition()));
			this->unscheduleUpdate();
			m_label->setText(_text("lingqu"));
		}

	}
}


