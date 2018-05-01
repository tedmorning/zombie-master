#include "FailLayer.h"
#include "tool.h"
#include "TString.h"
#include "BattleManage.h"
#include "GameMainMenu.h"
#include "ChoosePerson.h"
#include "StrengthLevelup.h"
#include "ZombieSound.h"
#include "data_center\RunningData.h"

CCScene* FailLayer::scene(int hero,int level)
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	FailLayer *layer = FailLayer::create(hero,level);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

FailLayer* FailLayer::create(int hero,int level)
{
	FailLayer *pRet = new FailLayer();
	pRet -> currentLevel = level;
	pRet -> currentHero = hero;
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

enum ButtonTag 
{
	ButtonTag_ChoosePerson = 72,
	ButtonTag_Intensify, 
	ButtonTag_GoMainpage,
	ButtonTag_RestartGame
};

bool FailLayer::init()
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
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/failLayer.ExportJson"));

	ui->setScale(0.8);
	addChild(ui, 2);

	//registerTouchEvent(ui, "choose_person", this, FailLayer::buttonClicked) ;
	registerTouchEvent(ui, "intensify", this, FailLayer::buttonClicked) ;
	registerTouchEvent(ui, "go_main_page", this, FailLayer::buttonClicked) ;
	registerTouchEvent(ui, "restart_game", this, FailLayer::buttonClicked) ;

	::playSound("music/lose.ogg");
	::playUIBackgroundMusic();
	
	UIImageView* pImageBg = imageObj_name(ui, "Image_10");
	UIImageView* pImageChat = imageObj_name(ui, "Image_28");
	UIImageView* pImageRole = imageObj_name(ui, "Image_41");
	pImageRole->setVisible(false);

	RoleSystem& roleSys = RunningData::getInstance()->getRoleSystem();
	Reinfoce& rf = RunningData::getInstance()->getReinfoce();
	ReinfoceSys rfOne = rf.m_reinfoceSys[1];
	ReinfoceSys rfTwo = rf.m_reinfoceSys[1];
	ReinfoceSys rfThree = rf.m_reinfoceSys[1];
	if(roleSys.m_roleInfos[k_ironmen].available == 0)
	{
		/*
		CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("ironmen_head.png");
		CCSprite* pRole = CCSprite::createWithSpriteFrameName("ironmen_head.png");
		CCRect rect = pRole->getTextureRect();
		CCPoint point = pRole->getTextureRect().origin;
		pRole->initWithTexture(pRole->getTexture(),CCRectMake(point.x+63,point.y+100,132,64),true);
		pRole->setPosition(ccp(350,230));
		addChild(pRole,10);
		*/
		pImageRole->setVisible(true);
		pImageRole->setScale(2);

		schedule(schedule_selector(FailLayer::roleOneBlink),2);
	} else if(rfOne.level == rfOne.maxLevel &&
				rfTwo.level == rfTwo.maxLevel &&
					rfThree.level == rfThree.maxLevel)
	{
		pImageChat->loadTexture("fail_chat_3.png",UI_TEX_TYPE_PLIST);
		CCSprite* pRole = CCSprite::createWithSpriteFrameName("shop_uniquekill_head.png");
		pRole->setPosition(ccp(320,240));
		addChild(pRole,10,12222);
		pRole->setScale(0.6);
	
		schedule(schedule_selector(FailLayer::roleTwoBlink),2);
	} else 
	{
		pImageChat->loadTexture("fail_chat_2.png",UI_TEX_TYPE_PLIST);
		CCSprite* pRole = CCSprite::createWithSpriteFrameName("shop_level_max.png");
		pRole->setPosition(ccp(320,240));
		addChild(pRole,10,12223);
		pRole->setScale(0.6);
		
		schedule(schedule_selector(FailLayer::roleThreeBlink),2);
	}

	return true;
}

void FailLayer::roleThreeBlink(float dt)
{
		CCNode* pRole = getChildByTag(12223);
		pRole->runAction(CCBlink::create(1,5));
}

void FailLayer::roleTwoBlink(float dt)
{
		CCNode* pRole = getChildByTag(12222);
		pRole->runAction(CCBlink::create(1,5));
}

void FailLayer::roleOneBlink(float dt)
{
		UIImageView* pImageRole = imageObj_name(ui, "Image_41");
		pImageRole->runAction(CCBlink::create(1,5));
}

void FailLayer::buttonClicked(CCObject *pSender, TouchEventType eType)
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
	case ButtonTag_ChoosePerson:
		{
			CCLOG("nextLevel") ;
			RunningData::getInstance()->currentHero = currentHero;
           // CCDirector::sharedDirector()->replaceScene(BattleManage::scene(currentHero,((currentLevel + 1) > 12?12:(currentLevel + 1) )));  // 目前只写了三关的数据
			CCDirector::sharedDirector()->replaceScene(ChoosePerson::scene());
		}
		
		break;
	
	case ButtonTag_Intensify:
		{
			CCLOG("backTomain") ;
            //CCDirector::sharedDirector()->replaceScene(GameMainMenu::scene());
		//	CCDirector::sharedDirector()->replaceScene(StrengthLevelup::scene());
			RunningData::getInstance()->isFromStrengthLevelupPage = true;
			CCDirector::sharedDirector()->pushScene(StrengthLevelup::scene());
		}
		break;

	case ButtonTag_GoMainpage:
		{
			CCLOG("reagain!") ;
			CCDirector::sharedDirector()->replaceScene(GameMainMenu::scene(false));
			//CCDirector::sharedDirector()->popToRootScene();
		}
		break;
	
	case ButtonTag_RestartGame:
		{
			CCLOG("reagain!") ;
            //CCDirector::sharedDirector()->replaceScene(BattleManage::scene( currentHero,currentLevel,false));
			RunningData::getInstance()->currentHero = currentHero;
			CCDirector::sharedDirector()->replaceScene(ChoosePerson::scene());
		}
		break;

	default:
		break;
	}
	
}
