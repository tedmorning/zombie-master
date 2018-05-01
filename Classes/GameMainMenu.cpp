#include "GameMainMenu.h"
#include "tool.h"
#include "BattleManage.h"
#include "TString.h"
#include "SimpleAudioEngine.h"
#include "ChoosePerson.h"
#include "LevelInstruction.h"
#include "StrengthLevelup.h"
#include "WinLayer.h"
#include "data_center\RunningData.h"
#include "ZombieSound.h"
#include "JniCommon.h"
#include "StoryScene.h"
#include "shopping_page.h"
#include "achievement_page.h"
#include "MultiTipsScene.h"
#include "GiftLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
#include "MobClickCpp.h"
#endif
enum ButtonTag 
{
	ButtonTagmusicBar  = 9,
	ButtonTagStoryLine,  //10
	ButtonTagIntensify, //11
	ButtonTagChallenge, //12
	ButtonTagShop,      //13
	ButtonTagBack,       //14
	ButtonTagButton_music = 4488,
	ButtonTagButton_achievement = 5183,
	ButtonTagShop_1 = 4765
};

CCScene* GameMainMenu::scene(bool isBegin)
{
	CCScene *scene = CCScene::create();


	// 'layer' is an autorelease object
	GameMainMenu *layer = GameMainMenu::create(isBegin);
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

GameMainMenu* GameMainMenu::create(bool isBegin)
{
	GameMainMenu *pRet = new GameMainMenu();
	pRet->isBegin = isBegin;

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

bool GameMainMenu::init()
{
	if (!CCLayer::init())
		return false;

	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//当前层的位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//#include "support/zip_support/ZipUtils.h"
	//ZipUtils::ccSetPvrEncryptionKey(0xf8f5ea10, 0x27ddeba6, 0xe59253c6,0x1b63fa3e);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("test001.plist");


	ui = TouchGroup::create();
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/GameMainMenu_1.ExportJson"));

	addChild(ui, 2);

//	imageObj_name(ui, "zom_logo")->loadTexture("game_name_logo.png");
	 

	UIButton *storyline = buttonObj_name(ui,"storyline");
	UIButton *intensify = buttonObj_name(ui,"intensify");
	UIButton *challenge = buttonObj_name(ui,"challenge");
	UIButton *shop = buttonObj_name(ui,"shop");
	shop -> setVisible(false);
	shop -> setTouchEnabled(false);

	UIImageView* shopimage = imageObj_name(ui, "Image_92");
	//shopimage->setVisible(false);

	UIButton *back = buttonObj_name(ui,"back");

//	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("main_gift.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("achievement.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui_prompt.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shopping.plist");

	//隐藏
	UIImageView* pImageTip = imageObj_name(ui, "Image_10");
	pImageTip->setVisible(false);

	UILabel* pLabelOne = labelObj_name(ui, "Label_tip_1");
	pLabelOne->setVisible(false);

	//UILabel* pLabelTwo = labelObj_name(ui, "Label_tip_2");
	//pLabelTwo->setVisible(false);

	UIButton* pButton = buttonObj_name(ui, "shop_1");
	//pButton->setVisible(false);

	UIImageView* pImageRight = imageObj_name(ui, "image_right");
	pImageRight->setVisible(false);
	UIImageView* pImageLeft = imageObj_name(ui, "image_left");
	pImageLeft->setVisible(false);

	UIImageView* pImageChatshow = imageObj_name(ui, "big_role_chat_show");
	pImageChatshow->setVisible(false);
	UIImageView* pImageRoleshow = imageObj_name(ui, "Image_role_show");
	pImageRoleshow->setVisible(false);

	opacityTip = 255;
	opacityTipTwo = 0;
	
	leftRotation = 0;
	rightRotation = 360;

	rotationOffset = 8;

	if(isBegin)
	{
	
		UIButton* pButtonStoryline = buttonObj_name(ui, "storyline");
		pButtonStoryline->setVisible(false);

		UIButton* pButtonChallenge = buttonObj_name(ui, "challenge");
		pButtonChallenge->setVisible(false);

		UIButton* pButtonIntensify = buttonObj_name(ui, "intensify");
		pButtonIntensify->setVisible(false);
	
		UIImageView* pImageScrollRight = imageObj_name(ui, "scroll_right");
		pImageScrollRight->setPositionX(pImageScrollRight->getPositionX()+150);
		UIImageView* pImageScrollLeft = imageObj_name(ui, "scroll_left");
		pImageScrollLeft->setPositionX(pImageScrollLeft->getPositionX()-150);

		//Image_38 右侧静止轮子
		imageObj_name(ui, "Image_38")->setRotation(180);
		
		setButtonVisible(false); //设置按钮不可见

		pImageScrollLeft->runAction(CCSequence::createWithTwoActions(
			CCMoveTo::create(0.2,ccp(pImageScrollLeft->getPositionX()+150,pImageScrollLeft->getPositionY())),
			CCCallFunc::create(this,callfunc_selector(GameMainMenu::scheduleRotationLeft)
		)));
	
		pImageScrollRight->runAction(CCSequence::createWithTwoActions(
			CCMoveTo::create(0.2,ccp(pImageScrollRight->getPositionX()-150,pImageScrollRight->getPositionY())),
			CCCallFunc::create(this,callfunc_selector(GameMainMenu::scheduleRotationRight)
		)));
	}	else
	{
		buttonNameCallback(ui, "storyline", this, GameMainMenu::buttonClicked) ;
		buttonNameCallback(ui, "intensify", this, GameMainMenu::buttonClicked) ;
		buttonNameCallback(ui, "challenge", this, GameMainMenu::buttonClicked) ;
		buttonNameCallback(ui, "shop", this, GameMainMenu::buttonClicked) ;
		buttonNameCallback(ui, "shop_1", this, GameMainMenu::buttonClicked) ;
		buttonNameCallback(ui, "back", this, GameMainMenu::buttonClicked) ;
		buttonNameCallback(ui, "Button_music", this, GameMainMenu::buttonClicked) ;

		registerTouchEvent(ui, "achievement", this, GameMainMenu::buttonClicked) ;

		rotationOffset = 0.5f;
		schedule(schedule_selector(GameMainMenu::rotationRight));
		schedule(schedule_selector(GameMainMenu::rotationLeft));
		
	}


	initVolume();
	::playUIBackgroundMusic();
	

	int gift = RunningData::getInstance()->getResource().getGift();
// 
// 	if(gift != 1)
// 	{
// 		UIButton* pButton = buttonObj_name(ui, "shop_1");
// 		pButton->setVisible(false);
// 		pButton ->setTouchEnabled(false);
// 	}

	
	pButton->setVisible(false);
	pButton->setTouchEnabled(false);

	schedule(schedule_selector(GameMainMenu::letinvisible),0.01);



	//pEffectSprite = CCSprite::createWithSpriteFrameName("big_gift_effect_1.png");
	//pSprite->setPosition(pShop->getPosition());
//	pEffectSprite->setPosition(ccp(visibleSize.width*0.76,visibleSize.height*0.25));
//	addChild(pEffectSprite,100);
//	CCArray* pFrames = CCArray::createWithCapacity(10);

//	char tem[100];
//	for (int i = 1; i < 11; i++)
//	{
//		sprintf(tem, "big_gift_effect_%i.png",i);
//		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tem);
//		pFrames->addObject(frame);
//	}
//	CCAnimation *pAnimation = CCAnimation::createWithSpriteFrames(pFrames, 1.0 / 12.0);
//	pEffectSprite->runAction(CCRepeatForever::create(CCAnimate::create(pAnimation)));

	if (!CCUserDefault::sharedUserDefault()->getBoolForKey("jihuogame", false))
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("jihuogame", true);

		//umeng::MobClickCpp::event("js_buy03_click");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
		umeng::MobClickCpp::event("js_jihuo_success");
#endif

	}

	return true;
}

void GameMainMenu::setButtonVisible(bool visible)
{
	 buttonObj_name(ui, "shop_1")->setVisible(visible);
	 buttonObj_name(ui, "shop")->setVisible(false);
	 buttonObj_name(ui, "achievement")->setVisible(visible);
	 buttonObj_name(ui, "Button_music")->setVisible(visible);
	 buttonObj_name(ui, "back")->setVisible(visible);
	 imageObj_name(ui, "zom_logo")->setVisible(visible);
}


void GameMainMenu::rotationRight(float dt)
{
	rightRotation-=rotationOffset;
	if(rightRotation<0)
	{
		rightRotation = 360;
	}
	UIImageView* pImageScrollRight = imageObj_name(ui, "scroll_right");
	pImageScrollRight->setRotation(rightRotation);
}

void GameMainMenu::scheduleRotationRight()
{
	schedule(schedule_selector(GameMainMenu::rotationRight));
}
void GameMainMenu::scheduleRotationLeft()
{

	schedule(schedule_selector(GameMainMenu::rotationLeft));
	scheduleOnce(schedule_selector(GameMainMenu::stopRotation),1);
}
void GameMainMenu::rotationLeft(float dt)
{
	leftRotation+=rotationOffset;
	if(leftRotation>360)
	{
		leftRotation = 0;
	}
	UIImageView* pImageScrollLeft = imageObj_name(ui, "scroll_left");
	pImageScrollLeft->setRotation(leftRotation);
}

void GameMainMenu::stopRotation(float dt)
{
	unschedule(schedule_selector(GameMainMenu::rotationRight));
	unschedule(schedule_selector(GameMainMenu::rotationLeft));
	scheduleOnce(schedule_selector(GameMainMenu::showMenu),0.5);
}

void GameMainMenu::showMenu(float dt)
{


	bool firestlogin = CCUserDefault::sharedUserDefault()->getBoolForKey("firelogin", true);

	if (firestlogin)
	{
		CCUserDefault::sharedUserDefault()->setBoolForKey("firelogin", false);
		GiftLayer * giflayer = GiftLayer::create(k_pay_logingif_free);
		addChild(giflayer,100);
	}
	else
	{
		GiftLayer * giflayer = GiftLayer::create(k_pay_logingif);
		addChild(giflayer,100);
	}


	UIButton* pButtonStoryline = buttonObj_name(ui, "storyline");
	pButtonStoryline->setVisible(true);
	pButtonStoryline->setPositionX(pButtonStoryline->getPositionX()-pButtonStoryline->getContentSize().width);
	pButtonStoryline->runAction(CCSequence::createWithTwoActions(
			CCMoveTo::create(0.35,ccp(pButtonStoryline->getPositionX()+pButtonStoryline->getContentSize().width,
				pButtonStoryline->getPositionY())),
			CCCallFunc::create(this,callfunc_selector(GameMainMenu::scheduleShowButtonAndRoation)
		)));

	UIButton* pButtonChallenge = buttonObj_name(ui, "challenge");
	pButtonChallenge->setVisible(true);
	pButtonChallenge->setVisible(true);
	pButtonChallenge->setPositionX(pButtonChallenge->getPositionX()+pButtonChallenge->getContentSize().width);
	pButtonChallenge->runAction(CCMoveTo::create(0.35,
			ccp(pButtonChallenge->getPositionX()-pButtonChallenge->getContentSize().width,
				pButtonChallenge->getPositionY())));

	UIButton* pButtonIntensify = buttonObj_name(ui, "intensify");
	pButtonIntensify->setPositionX(pButtonIntensify->getPositionX()-pButtonIntensify->getContentSize().width);
	pButtonIntensify->setVisible(true);
	pButtonIntensify->runAction(CCMoveTo::create(0.35,
			ccp(pButtonIntensify->getPositionX()+pButtonIntensify->getContentSize().width,
				pButtonIntensify->getPositionY())));
}

void GameMainMenu::scheduleShowButtonAndRoation()
{
	buttonNameCallback(ui, "storyline", this, GameMainMenu::buttonClicked) ;
	buttonNameCallback(ui, "intensify", this, GameMainMenu::buttonClicked) ;
	buttonNameCallback(ui, "challenge", this, GameMainMenu::buttonClicked) ;
	buttonNameCallback(ui, "shop", this, GameMainMenu::buttonClicked) ;
	buttonNameCallback(ui, "shop_1", this, GameMainMenu::buttonClicked) ;
	buttonNameCallback(ui, "back", this, GameMainMenu::buttonClicked) ;
	buttonNameCallback(ui, "Button_music", this, GameMainMenu::buttonClicked) ;

    registerTouchEvent(ui, "achievement", this, GameMainMenu::buttonClicked) ;

	scheduleOnce(schedule_selector(GameMainMenu::showButtonAndRoation),0.5);
}
void GameMainMenu::showButtonAndRoation(float dt)
{
	rotationOffset = 0.5f;
	schedule(schedule_selector(GameMainMenu::rotationRight));
	schedule(schedule_selector(GameMainMenu::rotationLeft));

	scheduleOnce(schedule_selector(GameMainMenu::setButtonVisibleTrue),0.2);
}

void GameMainMenu::setButtonVisibleTrue(float dt)
{
	float opacity = 0;
	buttonObj_name(ui, "shop_1")->setOpacity(opacity); 
	buttonObj_name(ui, "shop")->setOpacity(opacity); 
	buttonObj_name(ui, "achievement")->setOpacity(opacity); 
	buttonObj_name(ui, "Button_music")->setOpacity(opacity); 
	buttonObj_name(ui, "back")->setOpacity(opacity); 
	imageObj_name(ui, "zom_logo")->setOpacity(opacity); 
	imageObj_name(ui, "Image_23")->setOpacity(opacity); 
	imageObj_name(ui, "Image_92")->setOpacity(opacity); 
	setButtonVisible(true);
	schedule(schedule_selector(GameMainMenu::fadeoutButton));
}
void GameMainMenu::onEnter()
{
	CCNode::onEnter();
	showTip(1);

	initVolume();
}

void GameMainMenu::showTip(float dt)
{

	if(RunningData::getInstance()->isMainTip)
	{
		
		MultiTipsScene* tips = MultiTipsScene::create(2);
	//	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(GameMainMenu::fadeoutTwoTip));
		//tips -> setCallFun(func);
		tips->setTipString(labelObj_name(ui, "Label_tip_2")->getStringValue());
		addChild(tips,2);


/*
		UIImageView* pImageTipChat = imageObj_name(ui, "big_role_chat_show");
		UIImageView* pImageTipRole = imageObj_name(ui, "Image_role_show");	
		pImageTipChat->setVisible(true);	
		pImageTipRole->setVisible(true);
*/

		RunningData::getInstance()->isMainTip = false;

//		schedule(schedule_selector(GameMainMenu::fadeoutTwoTip));
	}
}

void GameMainMenu::musicChanged(CCObject *pSender, TouchEventType eType)
{
	CCLOG("musicChanged!!!") ;

	UISlider *slider = dynamic_cast<UISlider*>(pSender) ;

	float percent = slider->getPercent();

	::setSoundVolume(percent);
}

void GameMainMenu::sceneTransitionEffect()
{

	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	UIButton* pButtonStoryline = buttonObj_name(ui, "storyline");
	UIButton* pButtonChallenge = buttonObj_name(ui, "challenge");
	UIButton* pButtonIntensify = buttonObj_name(ui, "intensify");
	
	UIImageView* pImageScrollRight = imageObj_name(ui, "scroll_right");
	UIImageView* pImageInnerScrollRight = imageObj_name(ui, "Image_38");

	UIImageView* pImageScrollLeft = imageObj_name(ui, "scroll_left");
	UIImageView* pImageInnerScrollLeft= imageObj_name(ui, "Image_29");




	pButtonStoryline->runAction(CCSequence::create(CCMoveTo::create(0.5f, ccp(pButtonStoryline->getPositionX() - size.width*0.5, pButtonStoryline->getPositionY()))
			,CCCallFunc::create(this,callfunc_selector(GameMainMenu::sceneTransition)),NULL));

	moveToLeft(pButtonIntensify);
	moveToLeft(pImageScrollLeft);
	moveToLeft(pImageInnerScrollLeft);
	moveToLeft(buttonObj_name(ui, "shop_1"));

	moveToRight(pButtonChallenge);
	moveToRight(pImageScrollRight);
	moveToRight(pImageInnerScrollRight);
	moveToRight( buttonObj_name(ui, "shop"));
	moveToRight(buttonObj_name(ui, "achievement"));
	moveToRight(buttonObj_name(ui, "Button_music"));
	moveToRight(buttonObj_name(ui, "back"));
	 
	UIImageView* pImageLogo = imageObj_name(ui, "zom_logo");
	pImageLogo->runAction(CCMoveTo::create(0.5f, ccp(pImageLogo->getPositionX(), pImageLogo->getPositionY()+ size.height *0.5 )));

//	pEffectSprite->setVisible(false);
}

void GameMainMenu::moveToRight(CCNode* pSender)
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	pSender->runAction(CCMoveTo::create(0.5f, ccp(pSender->getPositionX() + size.width*0.5, pSender->getPositionY())));
}

void GameMainMenu::moveToLeft(CCNode* pSender)
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	pSender->runAction(CCMoveTo::create(0.5f, ccp(pSender->getPositionX() - size.width*0.5, pSender->getPositionY())));
}


void GameMainMenu::sceneTransition(){

	switch (m_tag)
	{
	case ButtonTagButton_achievement:
		{
			CCDirector::sharedDirector()->replaceScene(AchievementPage::scene());
		}
		break;
	case ButtonTagStoryLine:
		{
			CCLOG("storyLine mode start!") ;
			int stage = RunningData::getInstance()->getGameLevel().getStage();
			if(stage == 1)
			{
				CCDirector::sharedDirector()->replaceScene(StoryScene::scene(0,true));
			} else 
			{
				CCDirector::sharedDirector()->replaceScene(ChoosePerson::scene());
			}
		
		}
		
		break;

		case ButtonTagIntensify:
		{
			CCLOG("intensify mode start!") ;
			RunningData::getInstance()->isFromGameMainPage = true;
			CCDirector::sharedDirector()->replaceScene(StrengthLevelup::scene());
			//CCDirector::sharedDirector()->pushScene(CCTransitionFlipX::create(1.0f, ChoosePerson::scene()));
		}

		break;

		case ButtonTagChallenge:
		{
			CCLOG("challenge mode start!") ;
			CCDirector::sharedDirector()->replaceScene(LevelInstruction::scene(true));
		}

		break;

	default:
		break;
	}
/*	
	UIImageView* pImageLeft = imageObj_name(ui, "image_left");
	UIImageView* pImageRight = imageObj_name(ui, "image_right");

	pImageLeft->setPosition(left);
	pImageRight->setPosition(right);*/
	//pEffectSprite->setVisible(true);
}

void GameMainMenu::fadeoutOneTip(float dt)
{
		opacityTip-=2;

		UIImageView* pImageTip = imageObj_name(ui, "Image_10"); //提示框
		UILabel* pLabelOne = labelObj_name(ui, "Label_tip_1");

		if(opacityTip<0)
		{
			opacityTip = 255;
			pImageTip->setVisible(false);
			pLabelOne->setVisible(false);
			unschedule(schedule_selector(GameMainMenu::fadeoutOneTip));
		}

		pImageTip->setOpacity(opacityTip);
		pLabelOne->setOpacity(opacityTip);
}

void GameMainMenu::fadeoutButton(float dt)
{
		opacityTipTwo++;		

		if(opacityTipTwo>255)
		{
			opacityTipTwo = 255;

			unschedule(schedule_selector(GameMainMenu::fadeoutButton));
		}
		

		buttonObj_name(ui, "shop_1")->setOpacity(opacityTipTwo); 
		buttonObj_name(ui, "shop")->setOpacity(opacityTipTwo); 
		buttonObj_name(ui, "achievement")->setOpacity(opacityTipTwo); 
		buttonObj_name(ui, "Button_music")->setOpacity(opacityTipTwo); 
		buttonObj_name(ui, "back")->setOpacity(opacityTipTwo); 
		imageObj_name(ui, "zom_logo")->setOpacity(opacityTipTwo); 
		imageObj_name(ui, "Image_23")->setOpacity(opacityTipTwo); 
		imageObj_name(ui, "Image_92")->setOpacity(opacityTipTwo); 
}

void GameMainMenu::letinvisible(float dt)
{
	UIButton* pButton = buttonObj_name(ui, "shop_1");
	pButton->setVisible(false);
// 	int gift = RunningData::getInstance()->getResource().getGift();
// 
// 	if(gift != 1)
// 	{
// 		UIButton* pButton = buttonObj_name(ui, "shop_1");
// 		pButton->setVisible(false);
// 	}

}

void GameMainMenu::buttonClicked(CCObject *pSender, TouchEventType eType)
{
	
	if (eType != TOUCH_EVENT_ENDED)
	{
		return;
	}

	::playSound("music/click.ogg");

	imageObj_name(ui, "Image_13")->setVisible(false);//剧情等模式的遮挡


	UIButton *button = dynamic_cast<UIButton*>(pSender) ;
	m_tag = button->getTag();

	if(m_tag == ButtonTagBack)
	{
		//::exitGame();

		//弹出退出礼包

		GiftLayer * gift = GiftLayer::create(k_pay_exit);

		addChild(gift,100);

		return;
	} else if(m_tag == ButtonTagButton_music)
	{
		Config& config = RunningData::getInstance()->getConfig();
		UIButton* pButton = buttonObj_name(ui,"Button_music");
		float volume = config.getSoundVolume();

		if(volume > 0)
		{
			volume = 0;
			pButton->loadTextureNormal("music_off.png",UI_TEX_TYPE_PLIST);
			pButton->loadTexturePressed("music_button.png",UI_TEX_TYPE_PLIST);
			::setSoundVolume(volume);
		} else 
		{
			volume = 50;
			pButton->loadTextureNormal("music_button.png",UI_TEX_TYPE_PLIST);
			pButton->loadTexturePressed("music_off.png",UI_TEX_TYPE_PLIST);
			::setSoundVolume(volume);
		}

		
		config.setSoundVolume(volume);
		config.save();

		return;
	} else if(m_tag == ButtonTagShop)
	{
		//成功回调
		m_successCallback = [=](){
			//金币x150000、必杀x15、护盾x15
			Resource& resource = RunningData::getInstance()->getResource();
			resource.addGold(150000);
			resource.addShield(15);
			resource.addUniqueKill(15);

			resource.save();
		};
		//失败回调
		m_failCallback = [=](){
		};

		//pauseSchedulerAndActions();

		Shopping& shopping = RunningData::getInstance()->getShopping();
		shopping.setCatalog(k_supply);
		shopping.setIndex(k_give_big_gife);
	
		ShoppingLayer* pShopping = ShoppingLayer::create();
		addChild(pShopping,11);
		pShopping->setSuccessCallFun(m_successCallback);
		pShopping->setFailCallFun(m_failCallback);

		return;
	
	} 
	else if(m_tag == ButtonTagShop_1)
	{
		//成功回调
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		m_successCallback = [=](){
			//金币x150000、必杀x15、护盾x15
			Resource& resource = RunningData::getInstance()->getResource();
			resource.addGold(500);
			resource.setGift(0);
			resource.save();

			buttonObj_name(ui, "shop_1")->setTouchEnabled(false);
			//resumeSchedulerAndActions();
		};
		//失败回调
		m_failCallback = [=](){
		};

		//pauseSchedulerAndActions();

		Shopping& shopping = RunningData::getInstance()->getShopping();
		shopping.setCatalog(k_supply);
		shopping.setIndex(k_thinksgiving);


		ShoppingLayer* pShopping = ShoppingLayer::create();
		addChild(pShopping,11);
		pShopping->setSuccessCallFun(m_successCallback);
		pShopping->setFailCallFun(m_failCallback);

		return;
#endif
	} else if(m_tag == ButtonTagIntensify)
	{
			CCLOG("intensify mode start!") ;

			int stage = RunningData::getInstance()->getGameLevel().getStage();
			if(stage == 1)
			{
				int isWinOne = RunningData::getInstance()->getGameLevel().getIsWinOne();
				//bool isWinOne = CCUserDefault::sharedUserDefault()->getBoolForKey("lock",true);
				if(isWinOne==0)
				{
					UIImageView* pCurImageTip = imageObj_name(ui, "Image_10"); //提示框
					pCurImageTip->setVisible(true);
					pCurImageTip->setOpacity(255);

					UILabel* pCurLabel = labelObj_name(ui, "Label_tip_1");
					pCurLabel->setVisible(true);
					pCurLabel->setOpacity(255);

					pCurLabel->setText(_text("lock"));
					schedule(schedule_selector(GameMainMenu::fadeoutOneTip));

					return;
				}
			} 
			
		
			//CCDirector::sharedDirector()->pushScene(CCTransitionFlipX::create(1.0f, ChoosePerson::scene()));
		}
	 else if(m_tag == ButtonTagChallenge)
		{

			CCLOG("challenge mode start!") ;
			int isWinOne = RunningData::getInstance()->getGameLevel().getIsWinOne();
			//bool isWinOne = CCUserDefault::sharedUserDefault()->getBoolForKey("lock",true);
			if (isWinOne == 0)
			{
				UIImageView* pImageTip = imageObj_name(ui, "Image_10"); //提示框
				pImageTip->setVisible(true);
				pImageTip->setOpacity(255);

				UILabel* pLabelOne = labelObj_name(ui, "Label_tip_1");
				pLabelOne->setVisible(true);
				pLabelOne->setOpacity(255);

			
				pLabelOne->setText(_text("lock"));

				schedule(schedule_selector(GameMainMenu::fadeoutOneTip));

				return;
			}
		} else if(m_tag == ButtonTagStoryLine)
		{
			int stage = RunningData::getInstance()->getGameLevel().getStage();
			if(stage == 1)
			{
				int isWinOne = RunningData::getInstance()->getGameLevel().getIsWinOne();
				if(isWinOne == 1)
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

					sceneTransitionEffect();

				};
				//失败回调
				m_failCallback = [=](){

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
			} 
		}

	sceneTransitionEffect();

}

void GameMainMenu::initVolume()
{
	//读本地数据
	Config& config = RunningData::getInstance()->getConfig();

	float volume = config.getSoundVolume();

	UIButton* pButton = buttonObj_name(ui,"Button_music");

	if(volume>0)
	{
		pButton->loadTextureNormal("music_button.png",UI_TEX_TYPE_PLIST);
		pButton->loadTexturePressed("music_off.png",UI_TEX_TYPE_PLIST);
		::setSoundVolume(volume);
	} else 
	{
		pButton->loadTextureNormal("music_off.png",UI_TEX_TYPE_PLIST);
		pButton->loadTexturePressed("music_button.png",UI_TEX_TYPE_PLIST);
		::setSoundVolume(volume);
	}
}
