#include "PauseLayer.h"
#include "tool.h"
#include "TString.h"
#include "BattleManage.h"
#include "shopping_page.h"
#include "data_center\RunningData.h"
#include "ZombieSound.h"
#include "GameMainMenu.h"

enum ButtonTag 
{
	ButtonTagContinue = 10,
	ButtonTagBackToMain, //11
	ButtonTagMusicEffect, //12
	ButtonTagAddHudun,      //13
	ButtonTagAddBisha       //14
};

CCScene* PauseLayer::scene()
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	PauseLayer *layer = PauseLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool PauseLayer::init()
{
	if (!CCLayer::init())
		return false;

	moveIn(this);
	CCSprite* pBackground = CCSprite::createWithTexture(BattleManage::oneself->getScreenCapture(true)->getSprite()->getTexture());
	pBackground->setPosition(ccp(400.0, 240.0));
	pBackground->setFlipY(true);
	addChild(pBackground);
	
	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//当前层的位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCLayerColor* layercolor = CCLayerColor::create(ccc4(0,0,0,150),800,480) ;
	addChild(layercolor) ;

	ui = TouchGroup::create();
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/pauseLayer.ExportJson"));

	addChild(ui, 2);

	registerTouchEvent(ui, "continue", this, PauseLayer::buttonClicked) ;
	registerTouchEvent(ui, "backtomain", this, PauseLayer::buttonClicked) ;
	registerTouchEvent(ui, "musiceffect", this, PauseLayer::buttonClicked) ;
	registerTouchEvent(ui, "addhudun", this, PauseLayer::buttonClicked) ;
	registerTouchEvent(ui, "addbisha", this, PauseLayer::buttonClicked) ;

	::playUIBackgroundMusic();


	Config& config = RunningData::getInstance()->getConfig();

	UIImageView* pImageView = imageObj_name(ui,"musiceffet_icon");
	float volume = config.getSoundVolume();

	if(volume > 0)
	{
		pImageView->loadTexture("music_button.png",UI_TEX_TYPE_PLIST);
	} else 
	{
		pImageView->loadTexture("music_off.png",UI_TEX_TYPE_PLIST);
	}
	return true;
}

void PauseLayer::buttonClicked(CCObject *pSender, TouchEventType eType)
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
	case ButtonTagContinue:
		{
			CCLOG("storyLine mode start!") ;
			setEnableAll(ui->getWidgetByName("Panel_1"), false);
			CCDirector::sharedDirector()->popScene();
		}
		
		break;
	case ButtonTagBackToMain:
		{
			CCLOG("intensify mode start!") ;
			//CCDirector::sharedDirector()->popToRootScene();
			CCDirector::sharedDirector()->replaceScene(GameMainMenu::scene(false));
		}

		break;

	case ButtonTagMusicEffect:
		{
			CCLOG("challenge mode start!") ;
			Config& config = RunningData::getInstance()->getConfig();

			UIImageView* pImageView = imageObj_name(ui,"musiceffet_icon");
			float volume = config.getSoundVolume();

			if(volume > 0)
			{
				volume = 0;
				pImageView->loadTexture("music_off.png",UI_TEX_TYPE_PLIST);
				::setSoundVolume(volume);
			} else 
			{
				volume = 50;
				pImageView->loadTexture("music_button.png",UI_TEX_TYPE_PLIST);
				::setSoundVolume(volume);
			}

			config.setSoundVolume(volume);
			config.save();
			//CCDirector::sharedDirector()->replaceScene(CCTransitionFlipX::create(1.0f, BattleManage::scene()));
		}

		break;
	case ButtonTagAddHudun:
		{
			Shopping& shopping = RunningData::getInstance()->getShopping();
			shopping.setCatalog(k_supply);
			shopping.setIndex(k_shield);
			shoppingSupply(ButtonTagAddHudun);
			CCLOG("ButtonTagAddHudun!") ;
		}

		break;

	case ButtonTagAddBisha:
		{
			Shopping& shopping = RunningData::getInstance()->getShopping();
			shopping.setCatalog(k_supply);
			shopping.setIndex(k_unique_kill);
			shoppingSupply(ButtonTagAddBisha);
			CCLOG("ButtonTagAddBisha!") ;
		}

		break;

	default:
		break;
	}
	
}


void PauseLayer::shoppingSupply(int tag)
{
	//成功回调
	m_successCallback = [=](){
		Resource& resource = RunningData::getInstance()->getResource();

		if(tag == ButtonTagAddBisha)
		{
			resource.addUniqueKill(5);

		} else if(tag == ButtonTagAddHudun)
		{
			resource.addShield(5);

		}

		resource.save(); //保存
	
	};

	m_failCallback = [=]()
	{};
	
	ShoppingLayer* pShopping = ShoppingLayer::create();
	addChild(pShopping,11);
	pShopping->setSuccessCallFun(m_successCallback);
	pShopping->setFailCallFun(m_failCallback);

}

