#include "LevelInstruction.h"
#include "tool.h"
#include "TString.h"
#include "BattleManage.h"
#include "ZombieSound.h"
#include "data_center\RunningData.h"
#include "shopping_page.h"
#include "GameMainMenu.h"

enum ButtonTag 
{
	ButtonTagAttact = 10,
	ButtonTagBack
};

CCScene* LevelInstruction::scene(bool isrepeat)
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	LevelInstruction *layer = LevelInstruction::create(isrepeat);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void LevelInstruction::watch(float dt)
{
	if(isBuyFail)
	{
		isBuyFail = false;
		CCDirector::sharedDirector()->replaceScene(GameMainMenu::scene(false));
	}
}

LevelInstruction* LevelInstruction::create(bool isrepeat)
{
	LevelInstruction *pRet = new LevelInstruction();
	pRet -> isrepeatGame = isrepeat;

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

bool LevelInstruction::init()
{
	if (!CCLayer::init())
		return false;

	moveIn(this);
	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//当前层的位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCLayerColor* layercolor = CCLayerColor::create(ccc4(0,0,0,150),800,480) ;
	addChild(layercolor) ;

	ui = TouchGroup::create();  
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/LevelInstruction.ExportJson"));

	addChild(ui, 2);

	registerTouchEvent(ui, "attact", this, LevelInstruction::buttonClicked) ;
	registerTouchEvent(ui, "back", this, LevelInstruction::buttonClicked) ;
	

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("chapter.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/GameMainMenu_1/GameMainMenu_11.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("UI/GameMainMenu_1/GameMainMenu_14.plist");

	UIImageView* pRoleChat = imageObj_name(ui, "role_chat");
	pRoleChat->setVisible(false);

	RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
	Role r = rs.getCurrentRole();
	
	UIImageView* pRoleShow = imageObj_name(ui, "role_show");
	pRoleShow->setVisible(false);
//	pRoleShow->loadTexture(r.role_image.c_str());

	GameLevel& gl = RunningData::getInstance()->getGameLevel();
	if(isrepeatGame)
	{
		bgShow(gl.getForeverLevelInfo());
	} else 
	{
		bgShow(gl.getCurrentLevelInfo());
	}



	::playUIBackgroundMusic();

	ischat = false;
	isBuyFail = false;

	schedule(schedule_selector(LevelInstruction::watch),0.1);

	return true;
}

void LevelInstruction::bgShow(LevelInfo& li)
{
		UILabel* pUILabel = labelObj_name(ui, "description");
		pUILabel->setText(li.desp.c_str());

		if(isrepeatGame)
		{
			pUILabel->setVisible(false);
			UILabel* pUILabelTwo = UILabel::create();
			pUILabelTwo->setPosition(ccp(pUILabel->getPositionX()+8,pUILabel->getPositionY()-25));
			pUILabelTwo->setText(li.desp.substr(15,30));
			pUILabelTwo->setFontName("微软雅黑");
			pUILabelTwo->setFontSize(17);
			pUILabelTwo->setColor(ccc3(255,0,0));
			pUILabel->getParent()->addChild(pUILabelTwo);

			UILabel* pUILabelOne = UILabel::create();
			pUILabelOne->setPosition(pUILabel->getPosition());
			pUILabelOne->setText(li.desp.substr(0,12));
			pUILabelOne->setFontName("微软雅黑");
			pUILabelOne->setFontSize(17);
			pUILabelOne->setColor(ccc3(255,255,255));
			pUILabel->getParent()->addChild(pUILabelOne);
		}

		UIImageView* pBackground= imageObj_name(ui, "battle_background");
	//	pBackground->loadTexture(li.background.c_str());

		pBackground->loadTexture("battle_bg.jpg");
		UIImageView* pTitle = imageObj_name(ui, "chapter_num");
		pTitle->loadTexture(li.title.c_str(), UI_TEX_TYPE_PLIST);

		int stage = RunningData::getInstance()->getGameLevel().getStage();
		if(stage == 1)
		{  //通过第一关并获胜
			int isWinOne = RunningData::getInstance()->getGameLevel().getIsWinOne();
			if(isWinOne == 1)
			{
				GameLevel& gl = RunningData::getInstance()->getGameLevel();
				pTitle->loadTexture(gl.m_levelInfos.at(1).title.c_str(), UI_TEX_TYPE_PLIST);
			}
		}
		
}

void LevelInstruction::roleShow()
{
	RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
	Role r = rs.getCurrentRole();

	UIImageView* pRoleShow = imageObj_name(ui, "role_show");
	pRoleShow->setVisible(true);
	pRoleShow->loadTexture(r.role_image.c_str(),UI_TEX_TYPE_PLIST);

	CCDelayTime* delayTimeChat = CCDelayTime::create(0.3f);
	CCFiniteTimeAction* seq = CCSequence::create(delayTimeChat,  CCCallFunc::create(this, callfunc_selector(LevelInstruction::roleChat)), NULL);
	pRoleShow->runAction(seq);

}

void LevelInstruction::roleChat()
{
	if(ischat) return;

	ischat = true;
	RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
	Role r = rs.getCurrentRole();

	UIImageView* pRoleChat = imageObj_name(ui, "role_chat");
	//pRoleChat->loadTexture(r.role_chat_image.c_str());
	
	UILabel* pChatFont = labelObj_name(ui, "role_chat_font");
	pChatFont->setText(r.role_chat_image.c_str());

	/*
	if(r.id == 1)
	{
		
		pRoleChat->setPositionX(pRoleChat->getPositionX()+50);
		pRoleChat->loadTexture(r.role_chat_image.c_str(), UI_TEX_TYPE_PLIST);
	}

	if(r.id == 2)
	{
		pRoleChat->loadTexture(r.role_chat_image.c_str(), UI_TEX_TYPE_PLIST);
	}
	if(r.id == 3)
	{
		pRoleChat->loadTexture(r.role_chat_image.c_str(), UI_TEX_TYPE_PLIST);

		pRoleChat->setPositionX(pRoleChat->getPositionX()+50);
		pRoleChat->setPositionY(pRoleChat->getPositionY()-30);
	}
	*/
	pRoleChat->setVisible(true);

	CCDelayTime* delayTime = CCDelayTime::create(0.7f);
	CCCallFunc* callFunc = CCCallFunc::create(this, callfunc_selector(LevelInstruction::goBattle));
	CCFiniteTimeAction* seq = CCSequence::create(delayTime, callFunc, NULL);

	pRoleChat->runAction(seq);

}

void LevelInstruction::goBattle()
{
	GameLevel& gl = RunningData::getInstance()->getGameLevel();
	RoleSystem& rs = RunningData::getInstance()->getRoleSystem();

	int level = gl.getStage();
	int id = rs.getCurrentRole().id;
	
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

	ischat = false;

	CCDirector::sharedDirector()->replaceScene(BattleManage::scene(battleRoleId,level,isrepeatGame));
//	CCDirector::sharedDirector()->pushScene(CCTransitionFlipX::create(1.0f, BattleManage::scene(battleRoleId,level)));

}

void LevelInstruction::buttonClicked(CCObject *pSender, TouchEventType eType)
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
	case ButtonTagAttact:
		{

			int isWinOne = RunningData::getInstance()->getGameLevel().getIsWinOne();
			int stage = RunningData::getInstance()->getGameLevel().getStage();
			if(stage == 1 && isWinOne==1)
			{	
				//成功回调
				m_successCallback = [=](){
					//保存关卡数据
					GameLevel& gl = RunningData::getInstance()->getGameLevel();
					gl.addStage();
					gl.saveLevelInfo();
					
					Resource& res = RunningData::getInstance()->getResource();
					res.setShieldNum(res.getShieldNum() + 1);
					res.setUniqueKillNum(res.getUniqueKillNum() + 1);
					res.addGold(5000);
					res.save();
				};
				//失败回调
				m_failCallback = [=](){
					isBuyFail = true;
				};


				Shopping& shopping = RunningData::getInstance()->getShopping();
				shopping.setCatalog(k_supply);
				shopping.setIndex(k_give_gift);
	
				ShoppingLayer* pShopping = ShoppingLayer::create();
				addChild(pShopping,1003);
				pShopping->setSuccessCallFun(m_successCallback);
				pShopping->setFailCallFun(m_failCallback);	

				return;
			}
			CCLOG("attact!!!") ;
			//CCDirector::sharedDirector()->pushScene(CCTransitionFlipX::create(1.0f, ChoosePerson::scene()));
			roleShow();
		}
		
		break;

		case ButtonTagBack:
		{
			CCLOG("back!!!") ;
			if(isrepeatGame)
			{
				CCDirector::sharedDirector()->replaceScene(GameMainMenu::scene(false));
			} else 
			{
				CCDirector::sharedDirector()->popScene();
			}
			
			//CCDirector::sharedDirector()->popToRootScene();
		}
		
		break;
	
	default:
		break;
	}
	
}
