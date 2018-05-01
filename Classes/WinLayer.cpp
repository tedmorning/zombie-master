#include "WinLayer.h"
#include "tool.h"
#include "TString.h"
#include "BattleManage.h"
#include "GameMainMenu.h"
#include "StrengthLevelup.h"
#include "ZombieSound.h"
#include "LevelInstruction.h"
#include "ChoosePerson.h"
CCScene* WinLayer::scene(BattleResult br)
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	WinLayer *layer = WinLayer::create(br);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

WinLayer* WinLayer::create(BattleResult br)
{
	WinLayer *pRet = new WinLayer();
	pRet->m_br = br;

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
	ButtonTagNextLevel = 10,
	ButtonTagBackToMain, //11
	ButtonTagReAgain //12
};

bool WinLayer::init()
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
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/winLayer.ExportJson"));

	ui->setScale(0.8);
	addChild(ui, 2);

	registerTouchEvent(ui, "nextLevel", this, WinLayer::buttonClicked) ;
	registerTouchEvent(ui, "backtomain", this, WinLayer::buttonClicked) ;
	registerTouchEvent(ui, "reagain", this, WinLayer::buttonClicked) ;

	UILabel* pKillNum = labelObj_name(ui, "win_killed_num");
	UILabel* pRemainBlood = labelObj_name(ui, "win_remain_blood");
	UILabel* pGetGoldNum = labelObj_name(ui, "win_getgold_num");

	char tem[10];

	sprintf(tem, "%i", m_br.killedZombieNum);
	pKillNum->setText(tem);

	sprintf(tem, "%i%%", m_br.remainBlood);
	pRemainBlood->setText(tem);

	sprintf(tem, "%i", m_br.getGoldNum);
	pGetGoldNum->setText(tem);

	playSound("music/win.ogg");
	::playUIBackgroundMusic();

	return true;
}

void WinLayer::buttonClicked(CCObject *pSender, TouchEventType eType)
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
	case ButtonTagNextLevel:
		{
			CCLOG("nextLevel") ;
			GameLevel& gl = RunningData::getInstance()->getGameLevel();
			if (gl.getStage() == 2)
			{

				CCScene *scene = CCScene::create();

				// 'layer' is an autorelease object
				RunningData::getInstance()->currentHero = 1;
				ChoosePerson *layer = ChoosePerson::create();
				scene->addChild(layer);
				CCDirector::sharedDirector()->replaceScene(scene);
			}
			else
			CCDirector::sharedDirector()->replaceScene(LevelInstruction::scene(false));
			//CCDirector::sharedDirector()->popToSceneStackLevel(3);
			//CCDirector::sharedDirector()->replaceScene(BattleManage::scene(m_br.hero,((m_br.level + 1) > 12?12:(m_br.level + 1) ),false));  // 目前只写了三关的数据
		}
		
		break;
	case ButtonTagBackToMain:
		{
			CCLOG("backTomain") ;
		/*	if(RunningData::getInstance()->getGameLevel().getStage() == 1       //没有购买 
				|| RunningData::getInstance()->getGameLevel().getStage() == 2)//已购买
			{
				RunningData::getInstance()->isMainTip = true;
			*/
			CCDirector::sharedDirector()->replaceScene(GameMainMenu::scene(false));
		}
		break;

	case ButtonTagReAgain:
		{
			CCLOG("reagain!") ;
           // CCDirector::sharedDirector()->replaceScene(BattleManage::scene( currentHero,currentLevel));
		//	CCDirector::sharedDirector()->replaceScene(BattleManage::scene(m_br.hero,((m_br.level + 1) > 12?12:(m_br.level + 1) ),false));  
			CCDirector::sharedDirector()->pushScene(StrengthLevelup::scene());
		}
		break;

	default:
		break;
	}
	
}
