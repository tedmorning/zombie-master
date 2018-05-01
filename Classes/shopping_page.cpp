#include "shopping_page.h"
#include "tool.h"
#include "data_center\RunningData.h"
#include "ZombieSound.h"
#include "JniCommon.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "MobClickCpp.h"
#endif

enum ButtonTag 
{
	ButtonTag_Buy = 4477,
	ButtonTag_Cancel = 4487
};

static ShoppingLayer* sInstance = NULL;

bool ShoppingLayer::init()
{
	if (!CCLayer::init())
		return false;
	
	payID = "001";

	moveIn(this);
	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//当前层的位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCLayerColor* layercolor = CCLayerColor::create(ccc4(0,0,0,150),800,480) ;
	addChild(layercolor) ;

	Shopping& shopping = RunningData::getInstance()->getShopping();
	const ShoppingInfo& si = shopping.getShoppingInfo(shopping.getCatalog(), shopping.getIndex());
	
	ui = TouchGroup::create();
	if(shopping.getCatalog() == k_supply && shopping.getIndex() == k_give_gift)
	{
			ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/activateGame.ExportJson"));
			registerTouchEvent(ui, "shop_cancel", this, ShoppingLayer::buttonClicked);
			registerTouchEvent(ui, "shop_buy", this, ShoppingLayer::buttonClicked);
	} else 
	{
		ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/Shop.ExportJson"));
		registerTouchEvent(ui, "shop_cancel", this, ShoppingLayer::buttonClicked);
		registerTouchEvent(ui, "shop_buy", this, ShoppingLayer::buttonClicked);

		UIImageView* pShopTitleBig = imageObj_name(ui, "shop_title_big");
		UIImageView* pShopTitleSmalle = imageObj_name(ui, "shop_title_smalle");
		//UILabel* pDescriptionTwo = labelObj_name(ui, "shop_description");
		//UIImageView* pShopNumYuan = imageObj_name(ui, "shop_num_yuan");

		UIImageView* pGoldShow = imageObj_name(ui, "gold_show");
		UIImageView* pUniquekillShow = imageObj_name(ui, "uniquekill_show");
		UIImageView* pShieldShow = imageObj_name(ui, "shield_show");
		pGoldShow->setVisible(false);
		pUniquekillShow->setVisible(false);
		pShieldShow->setVisible(false);
		

		pShopTitleBig->loadTexture(si.title_big.c_str(), UI_TEX_TYPE_PLIST);
	//	pDescriptionTwo->setText(si.shop_description_1);
		//pShopNumYuan->loadTexture(si.num_yuan.c_str());

		if(shopping.getCatalog() == k_supply)
		{
			if(shopping.getIndex() == k_give_gift || shopping.getIndex() == k_give_big_gife)
			{
				pShopTitleSmalle->setVisible(false);

				if( shopping.getIndex() == k_give_big_gife)
				{
					pGoldShow->setVisible(true);
					pUniquekillShow->setVisible(true);
					pShieldShow->setVisible(true);

// 					UILabel* pDescriptionOne = labelObj_name(ui, "shop_description_1");
// 					UILabel* pDescriptionTwo = labelObj_name(ui, "shop_description_2");
// 					UILabel* pDescriptionThree = labelObj_name(ui, "shop_description_3");
// 				
// 					pDescriptionOne->setText(si.shop_description_1);
// 					pDescriptionOne->setPositionY(pGoldShow->getPositionY()-4);
// 					pDescriptionOne->setPositionX(pDescriptionOne->getPositionX() + 116);
// 					pDescriptionOne->setTextHorizontalAlignment(kCCTextAlignmentLeft);
// 
// 					pDescriptionTwo->setText(si.shop_description_2);
// 					pDescriptionTwo->setPositionY(pUniquekillShow->getPositionY()-4);
// 					pDescriptionTwo->setPositionX(pDescriptionTwo->getPositionX() + 116);
// 					pDescriptionTwo->setTextHorizontalAlignment(kCCTextAlignmentLeft);
// 
// 					pDescriptionThree->setText(si.shop_description_3);
// 					pDescriptionThree->setPositionY(pShieldShow->getPositionY()-4);
// 					pDescriptionThree->setPositionX(pDescriptionThree->getPositionX()+116);
// 					pDescriptionThree->setTextHorizontalAlignment(kCCTextAlignmentLeft);

				}

			} else
			{
				if(shopping.getIndex() == k_thinksgiving)
				{
// 					UILabel* pDescriptionThree = labelObj_name(ui, "shop_description_3");
// 					pDescriptionThree->setText(si.shop_description_2);
// 					pDescriptionThree->setPositionY(pDescriptionThree->getPositionY()+4);
				}
			
				if(shopping.getIndex() == k_getGold)
				{
					pShopTitleSmalle->setPositionY(pShopTitleSmalle->getPositionY()-15);
				//	pDescriptionTwo->setPositionY(pDescriptionTwo->getPositionY()-20);
					//pDescriptionTwo->setPositionX(pDescriptionTwo->getPositionX()-3);
				}
  
				if(shopping.getIndex() == k_unique_kill || shopping.getIndex() == k_shield)
				{
					pShopTitleSmalle->setPositionY(pShopTitleSmalle->getPositionY()-15);
				//	pDescriptionTwo->setPositionY(pDescriptionTwo->getPositionY()-20);
				//	pDescriptionTwo->setPositionX(pDescriptionTwo->getPositionX()-3);
				}

				if(shopping.getIndex() == k_rebirth)
				{
					pShopTitleSmalle->setPositionY(pShopTitleSmalle->getPositionY()-15);
					//pDescriptionTwo->setPositionY(pDescriptionTwo->getPositionY()-20);
					//pDescriptionTwo->setPositionX(pDescriptionTwo->getPositionX()+3);
				}

				pShopTitleSmalle->loadTexture(si.title_smalle.c_str(), UI_TEX_TYPE_PLIST);
			}
	
		} else
		{
			pShopTitleSmalle->loadTexture(si.title_smalle.c_str(), UI_TEX_TYPE_PLIST);
	
		}



		if(shopping.getCatalog() == 1)
		{
// 			UILabel* pDescriptionThree = labelObj_name(ui, "shop_description_3");
// 			pDescriptionThree->setText(si.shop_description_2);
// 			pDescriptionThree->setPositionY(pDescriptionThree->getPositionY()+20);
// 			pDescriptionThree->setPositionX(pDescriptionThree->getPositionX()-5);

			//pDescriptionTwo->setPositionY(pDescriptionTwo->getPositionY() + 12);
			//pDescriptionTwo->setPositionX(pDescriptionTwo->getPositionX()-5);
		}

		if(shopping.getCatalog() == k_role)
		{
// 			CCSprite* pRole = CCSprite::createWithSpriteFrameName("shop_lock_1.png");
// 			pRole->setPosition(pShopTitleSmalle->getPosition());
// 
// 			addChild(pRole,100);
// 			CCArray* pFrames = CCArray::createWithCapacity(3);
// 
// 			char tem[50];
// 			for (int i = 1; i < 3; i++)
// 			{
// 				sprintf(tem, "shop_lock_%i.png",i);
// 				CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tem);
// 				pFrames->addObject(frame);
// 			}
// 			CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(pFrames, 1.0 / 24.0);
// 
// 			pRole->runAction(CCRepeatForever::create(CCAnimate::create(pAnimation)));


	
		}

	}
	
	
	addChild(ui, 2);

	sInstance = this;

	return true;
}

void ShoppingLayer::buttonClicked(CCObject *pSender, TouchEventType eType)
{

	if (eType != TOUCH_EVENT_ENDED)
	{
		return;
	}

	::playSound("music/click.ogg");

	UIButton *button = dynamic_cast<UIButton*>(pSender) ;
	int tag = button->getTag() ;

	switch (tag)
	{
	case ButtonTag_Buy:
		{
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32/* || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID*/)

// 			successCallBack(true);
// 			return;
//#endif




			int index = RunningData::getInstance()->getShopping().getIndex();
			int catlog = RunningData::getInstance()->getShopping().getCatalog();
//#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)			
			// 缺少升至满级的计费点
			if(catlog == 1) // 技能
			{
				//savePaycode("4");
				//savePaycode("30000852696003");
				//savePaycode("30000842303704");
				//payID = "004";
				// 技能升级

				payCode(k_pay_fulllevel, this, Sel_Pay_Event(&ShoppingLayer::successCallBack));
			}
			else if (catlog == 2) // 角色
			{
				if (index == 1) // 黑寡妇
				{
					savePaycode("5");
					//savePaycode("30000852696004");
					//savePaycode("30000842303705");
					payID = "005";
				}
				else if (index == 2) // 擎天柱
				{
					savePaycode("6");
					//savePaycode("30000852696005");
					//savePaycode("30000842303706");
					payID = "006";
				}
				else
				{//金币补给
					savePaycode("2");
					//savePaycode("30000852696001");
					//savePaycode("30000842303702");
				}
					
			}
			else if (catlog == 3) // 补给
			{
				if (index == 0)
				{//金币补给
					payCode(k_pay_gold10000, this, Sel_Pay_Event(&ShoppingLayer::successCallBack));
				}
				else if (index == 1)//必杀
				{
				
					payCode(k_pay_bisha, this, Sel_Pay_Event(&ShoppingLayer::successCallBack));
			
				}
				else if(index == 2)//护盾
				{
					payCode(k_pay_hudun, this, Sel_Pay_Event(&ShoppingLayer::successCallBack));
				}
				else if(index == 3)//立即复活
				{  
					payCode(k_pay_revieve, this, Sel_Pay_Event(&ShoppingLayer::successCallBack));
				
				}
				else if(index == 4)
				{
					savePaycode("1");
					//savePaycode("30000842303701");
					payID = "001";
				}
				else if(index == 5)
				{//土豪金礼包
					savePaycode("9");
					//激战僵尸
					//savePaycode("30000852696008");
					//第一版计费
					//savePaycode("30000842303709");
					payID = "009";
				}
				else if(index == 6)
				{
					savePaycode("10");
					//savePaycode("30000852696009");
					//savePaycode("30000842303710");
					payID = "010";
				}
				else
				{
					savePaycode("2");
					//savePaycode("30000852696001");
					//savePaycode("30000842303702");
					payID = "002";
				}
			}
			else
			{
				// 默认情况下
				savePaycode("2");
				//savePaycode("30000852696001");
				//savePaycode("30000842303702");
				payID = "002";
			}
		//	payForProduct(ShoppingLayer::successCallBack);
//#endif	
		}

		break;
	case ButtonTag_Cancel:
		{
			// 失败
			::playSound("music/operationfail.ogg");
			CCLOG("ButtonTag_Cancel start!");
			
			int index = RunningData::getInstance()->getShopping().getIndex();
			int catlog = RunningData::getInstance()->getShopping().getCatalog();
			//if((index == k_rebirth || index == k_unique_kill || index == k_shield)
			//	&& catlog == k_supply)
			//{
			//	m_failFun();
			//}
			sInstance->showShoppingTip(false);
			m_failFun();
			
			removeFromParent();
		
		}

		break;

	default:
		break;
	}
	CCLog("222222222");
}

void ShoppingLayer::successCallBack(bool buyOver)
{
	CCLOG("ButtonTag_Buy over!!!");
	if (buyOver)
	{
		// 成功
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//umeng::MobClickCpp::buy(sInstance -> payID.c_str(), 1, 1000);
#endif

		
		this->scheduleOnce(SEL_SCHEDULE(&ShoppingLayer::buySuccess), 0.01);
		//buySuccess(0);
		
	} else
	{
		sInstance->showShoppingTip(false);
	}
}
void ShoppingLayer::buySuccess(float dt)
{
	::playSound("music/purchase.ogg");
	this->showShoppingTip(true);
	this->m_successFun();
	this->removeFromParent();
}

void ShoppingLayer::showShoppingTip(bool isSuccess)
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* sprite =NULL;

	if(isSuccess)
	{
		sprite = CCSprite::createWithSpriteFrameName("shopping_success.png");
	} else 
	{
		sprite = CCSprite::createWithSpriteFrameName("shopping_fail.png");
	}


	sprite->setPosition(ccp(size.width*0.5, size.height*0.15));
	sInstance->getParent()->addChild(sprite,2000);
	sprite->runAction(CCSequence::createWithTwoActions(CCFadeOut::create(3),CCCallFuncN::create(sprite,callfuncN_selector(ShoppingLayer::removeNode))));
	
}
void ShoppingLayer::removeNode(CCNode* pSender)
{
	pSender->removeFromParent();
}


void ShoppingLayer::setSuccessCallFun(std::function<void()> sfun)
{
	m_successFun = sfun;
}

void ShoppingLayer::setFailCallFun(std::function<void()> sfun)
{
	m_failFun = sfun;
}