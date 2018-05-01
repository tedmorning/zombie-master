#include "ChoosePerson.h"
#include "tool.h"
#include "TString.h"
#include "LevelInstruction.h"
#include "data_center\RunningData.h"
#include "EnemyData.h"
#include "shopping_page.h"
#include "ZombieSound.h"
#include "GameMainMenu.h"
#include "GiftLayer.h"
#include "LuckLayer.h"
static const int image_tag_operter = 10;
enum ButtonTag
{
	ButtonTagRole_1 = 401,
	ButtonTagRole_2 = 402,
	ButtonTagRole_3 = 403,

	ButtonTagBuyRole_1 = ButtonTagRole_1*image_tag_operter,
	ButtonTagBuyRole_2 = ButtonTagRole_2*image_tag_operter,
	ButtonTagBuyRole_3 = ButtonTagRole_3*image_tag_operter,

	ButtonTagBackToMain = 26,
	ButtonTagSure = 33
};

ChoosePerson::ChoosePerson()
:focusTag(ButtonTagRole_2)
{}

CCScene* ChoosePerson::scene()
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	ChoosePerson *layer = ChoosePerson::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool ChoosePerson::init()
{
	if (!CCLayer::init())
		return false;

	moveIn(this);
	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//当前层的位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCLayerColor* layercolor = CCLayerColor::create(ccc4(0,0,0,150),800,480) ;
	addChild(layercolor);

	ui = TouchGroup::create();
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/ChoosePerson.ExportJson"));

	addChild(ui, 2);
  
	registerTouchEvent(ui, "back", this, ChoosePerson::buttonClicked) ;
	registerTouchEvent(ui, "sure", this, ChoosePerson::buttonClicked) ;
	registerTouchEvent(ui, "role_3", this, ChoosePerson::buttonClicked) ;
	registerTouchEvent(ui, "role_2", this, ChoosePerson::buttonClicked) ;
	registerTouchEvent(ui, "role_1", this, ChoosePerson::buttonClicked) ;
	registerTouchEvent(ui, "operator_3", this, ChoosePerson::buttonClicked) ;
	registerTouchEvent(ui, "operator_2", this, ChoosePerson::buttonClicked) ;
	registerTouchEvent(ui, "operator_1", this, ChoosePerson::buttonClicked) ;
	
	
//	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("choosePerson.plist");
	
	//初始化角色信息
	initRoleInfo();

	//初始化角色动画
	initRoleAnimation();
	
	schedule(schedule_selector(ChoosePerson::lockBlink),2);

	return true;
}

void ChoosePerson::onEnter()
{
	CCLayer::onEnter();
	
	//initRoleInfo();
	showFocus(focusTag);
}
void ChoosePerson::initRoleAnimation()
{
	m_pRoleShow = RoleShow::create();
	UIImageView* pRoleShow = imageObj_name(ui, "role_show");
	CCPoint point = pRoleShow->getPosition();
	CCSize size =  pRoleShow->getContentSize();
	m_pRoleShow->setPosition(point);
	m_pRoleShow->resetArea(ccp(point.x-size.width*0.5, point.y-size.height*0.35), size);
	addChild(m_pRoleShow,10);
	if (focusTag == ButtonTagRole_1)
	{
		m_pRoleShow->showHeroAnimation(k_battle_wolverine, ccp(-size.width*0.05,size.height*0.45));
	} else if (focusTag == ButtonTagRole_2)
	{
		m_pRoleShow->showHeroAnimation(k_battle_blackwidow, ccp(-size.width*0.05,size.height*0.45));
	} else if(focusTag == ButtonTagRole_3)
	{
		m_pRoleShow->showHeroAnimation(k_battle_wolverine, ccp(-size.width*0.05,size.height*0.45));
		UIImageView* pRoleShow = imageObj_name(ui, "role_show");
		CCSize size =  pRoleShow->getContentSize();
		//因为ironmen没有枪
		m_pRoleShow->changeHero(k_battle_ironmen, ccp(size.width*0.1,size.height*0.45));
	}
	
}

void ChoosePerson::initRoleInfo()
{
	RoleSystem& rs = RunningData::getInstance()->getRoleSystem();

	//取得焦点
	for(int i=0; i<k_role_type_end; i++)
	{
		if(rs.m_roleInfos[i].available)
		{
			focusTag = ButtonTagRole_1+i;
		}
	}

	//如果战斗胜利后返回角色选择，则选择最后一个战斗的角色
	if(RunningData::getInstance()->currentHero > -1)
	{
		int id  = RunningData::getInstance()->currentHero;
		RunningData::getInstance()->currentHero = -1;

		if(id == 1)
		{
			focusTag = ButtonTagRole_2;
		} else if(id == 2)
		{
			focusTag = ButtonTagRole_1;
		} else if(id == 3)
		{
			focusTag = ButtonTagRole_3;
		} 
		
		
	}	for(int i=ButtonTagRole_1; i<=ButtonTagRole_3; i++)
	{
		//购买按钮初始化
		Role role = rs.m_roleInfos[i-ButtonTagRole_1];
		UIButton* pBuyRoleButton = buttonObj_tag(ui, i*image_tag_operter);
		UIImageView* pLockImage = imageObj_tag(ui,  i*image_tag_operter +1);
		UIButton* pOperator = buttonObj_tag(ui, i*image_tag_operter);

		if(role.available)
		{
			pBuyRoleButton->loadTextures(rs.getAvailableImage().c_str(),rs.getAvailableImage().c_str(),"",UI_TEX_TYPE_PLIST);
			pLockImage->setVisible(false);

			if(i == focusTag)
			{
				pOperator->loadTextures(rs.getUsingImage().c_str(), rs.getUsingImage().c_str(), "", UI_TEX_TYPE_PLIST);
				rs.setUsingRoleId(role.id);
			}
		} else 
		{
			pBuyRoleButton->loadTextures(rs.getDisableImage().c_str(),"","",UI_TEX_TYPE_PLIST);
		}

		UIButton* pBackgroundButton = buttonObj_tag(ui, i);

		//角色获取焦点初始化
		if (focusTag == i)
		{
			pBackgroundButton->loadTextures("gun_board.png", "gun_board.png", "", UI_TEX_TYPE_PLIST);
		
			UILabel* pLabelTitle = labelObj_name(ui, "role_desp_title");
			UILabel* pLabelBrief = labelObj_name(ui, "role_desp_brief");
			UILabel* pLabelSpeci = labelObj_name(ui, "role_desp_speci");
			
			Role role = rs.m_roleInfos[i-ButtonTagRole_1];
			pLabelTitle->setText(role.desp_title);
			pLabelBrief->setText(role.desp_brief);
			pLabelSpeci->setText(role.desp_speci);
	
			continue;
		} 
		pBackgroundButton->loadTextures("gun_board1.png", "gun_board1.png", "", UI_TEX_TYPE_PLIST);

	}

}

void ChoosePerson::showFocus(int tag)
{
	focusTag = tag;

	RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
	for(int i=ButtonTagRole_1; i<=ButtonTagRole_3; i++)
	{
		UIButton* pUIButton = buttonObj_tag(ui, i);
		UIButton* pOperator = buttonObj_tag(ui, i*image_tag_operter);

		Role& role = rs.m_roleInfos[i-ButtonTagRole_1];
		if (tag == i)
		{
			pUIButton->loadTextures("gun_board.png", "gun_board.png", "", UI_TEX_TYPE_PLIST);
			
			if(role.available)
			{
				pOperator->loadTextures(rs.getUsingImage().c_str(), rs.getUsingImage().c_str(), "", UI_TEX_TYPE_PLIST);
				rs.setUsingRoleId(i-ButtonTagRole_1 + 1);
			}

			UIImageView* pRoleShow = imageObj_name(ui, "role_show");
			CCSize size =  pRoleShow->getContentSize();

			int id = i-ButtonTagRole_1 + 1;

			//1,2 的ID互换
			int battleRoleId = 0;
			if(id == 1)
			{
				battleRoleId = 2;
			} else if(id == 2)
			{
				battleRoleId = 1;
			} else 
			{
				battleRoleId =id;
			}
			m_pRoleShow->changeHero(battleRoleId, ccp(size.width*0.1,size.height*0.45));

			continue;
		} 

		pUIButton->loadTextures("gun_board1.png", "gun_board1.png", "", UI_TEX_TYPE_PLIST);

		if(role.available)
		{
			pOperator->loadTextures(rs.getAvailableImage().c_str(), rs.getAvailableImage().c_str(), "", UI_TEX_TYPE_PLIST);
		}
	}

	//buyRole(tag*image_tag_operter);
}

void ChoosePerson::cascadeShow(int tag)
{
	RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
	Role role = rs.m_roleInfos[tag-ButtonTagRole_1];

//	UIImageView* pImageView = imageObj_name(ui, "role_image_show");
	
//	pImageView->loadTexture(role.role_image.c_str(), UI_TEX_TYPE_PLIST);
	
	UILabel* pLabelTitle = labelObj_name(ui, "role_desp_title");
	UILabel* pLabelBrief = labelObj_name(ui, "role_desp_brief");
	UILabel* pLabelSpeci = labelObj_name(ui, "role_desp_speci");
			
	pLabelTitle->setText(role.desp_title);
	pLabelBrief->setText(role.desp_brief);
	pLabelSpeci->setText(role.desp_speci);

}

void ChoosePerson::failCallback()
{
	CCLOG("failCallback");
}
void ChoosePerson::buyRole(int tag)
{
	RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
	int roleIndex = tag/image_tag_operter - ButtonTagRole_1;
	Role& role = rs.m_roleInfos[roleIndex];

	if(!role.available)
	{
	
		//成功回调
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		m_successCallback = [=](){
			
			RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
			UIImageView* pLockImage = imageObj_tag(ui,  tag +1);
			pLockImage->setVisible(false);

			UIButton* pBuyRoleButton = buttonObj_tag(ui, tag);
			if(role.available)
			{
				if(focusTag*image_tag_operter == tag)
				{
					pBuyRoleButton->loadTextures(rs.getUsingImage().c_str(),rs.getUsingImage().c_str(),"",UI_TEX_TYPE_PLIST);
					rs.setUsingRoleId(tag/image_tag_operter -ButtonTagRole_1 +1);
				} else 
				{
					pBuyRoleButton->loadTextures(rs.getAvailableImage().c_str(),rs.getAvailableImage().c_str(),"",UI_TEX_TYPE_PLIST);
				}
			}

			

	
		};

		m_failCallback = [=](){};

		Shopping& shopping = RunningData::getInstance()->getShopping();
		shopping.setCatalog(2);
		shopping.setIndex(roleIndex);
		//m_pRoleShow->pause();

		GiftLayer * giftLayer = NULL;
		if (roleIndex == k_blackwidow)
		{

			//giftLayer = GiftLayer::create(NEWGIFT);
			giftLayer = GiftLayer::create(k_pay_newgift);
			
		}
		else if (roleIndex == k_ironmen)
		{
			giftLayer = GiftLayer::create(k_pay_supergift);
			
			//LuckLayer::create();
// 			LuckLayer * luckyLayer = LuckLayer::create();
// 
// 			this->addChild(luckyLayer,11);
			
		}
		if (giftLayer)
		{
			giftLayer->setSuccessCallFun(m_successCallback);
			giftLayer->setFailCallFun(m_failCallback);
			addChild(giftLayer, 11);
		}
		
		//CCDirector::sharedDirector()->pushScene(GiftLayer::scene(giftLayer));
	

// 		ShoppingLayer* pShopping = ShoppingLayer::create();
// 		addChild(pShopping,11);
// 		pShopping->setSuccessCallFun(m_successCallback);
// 		pShopping->setFailCallFun(m_failCallback);
//#endif
	}
}

void ChoosePerson::lockBlink(float dt)
{
	RoleSystem& rs = RunningData::getInstance()->getRoleSystem();

	for(int i=ButtonTagRole_1; i<=ButtonTagRole_3; i++)
	{
		//购买按钮初始化
		Role role = rs.m_roleInfos[i-ButtonTagRole_1];
		UIButton* pBuyRoleButton = buttonObj_tag(ui, i*image_tag_operter);

		if(!role.available)
		{
			pBuyRoleButton->runAction(CCBlink::create(1,5));
		}

	}

}

void ChoosePerson::buttonClicked(CCObject *pSender, TouchEventType eType)
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
	case ButtonTagBuyRole_1:
	case ButtonTagBuyRole_2:
	case ButtonTagBuyRole_3:
		{
			buyRole(tag);
			CCLOG("BuyRole!") ;
			//CCDirector::sharedDirector()->popScene();
		}
		
		break;
	case ButtonTagRole_1:
	case ButtonTagRole_2:
	case ButtonTagRole_3:
		{
			showFocus(tag);
			//级联显示内容
			cascadeShow(tag);
			CCLOG("role!") ;
			//CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.0f, BattleManage::scene()));
		}

		break;
	case ButtonTagBackToMain:
		{
			CCLOG("backTomain") ;
			CCDirector::sharedDirector()->replaceScene(GameMainMenu::scene(false));
		}

		break;
	case ButtonTagSure:
		{

			RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
			Role& role = rs.m_roleInfos[focusTag - ButtonTagRole_1];
			if(!role.available) 
			{
				buyRole(focusTag*image_tag_operter);
				break;
			}

			m_pRoleShow->pause();
			CCDirector::sharedDirector()->pushScene(LevelInstruction::scene(false));
			//CCDirector::sharedDirector()->pushScene(CCTransitionFlipX::create(1.0f, LevelInstruction::scene()));
			//CCDirector::sharedDirector()->pushScene(CCTransitionFlipX::create(1.0f, BattleManage::scene()));

			CCLOG("sure!") ;
		}

		break;

	default:
		break;
	}
	
}

	