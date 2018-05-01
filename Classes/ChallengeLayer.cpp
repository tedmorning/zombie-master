#include "ChallengeLayer.h"
#include "tool.h"
#include "TString.h"
#include "BattleManage.h"
#include "GameMainMenu.h"
#include "StrengthLevelup.h"
#include "ZombieSound.h"
#include "data_center\RunningData.h"
#include "CCShake.h"


CCScene* ChallengeLayer::scene(int hero,int level, int  repeatTimes, int totolGold)
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	ChallengeLayer *layer = ChallengeLayer::create(hero, level, repeatTimes, totolGold);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


ChallengeLayer* ChallengeLayer::create(int hero,int level, int  repeatTimes, int totolGold)
{
	ChallengeLayer *pRet = new ChallengeLayer();
	pRet -> currentLevel = level;
	pRet -> currentHero = hero;
	pRet -> repeatTimes = repeatTimes;
	pRet -> totolGold = totolGold;
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
	ButtonTagStrenthLevel = 12,
	ButtonTagBackToMain = 11, 
	ButtonTagReAgain = 10 
};

bool ChallengeLayer::init()
{
	if (!CCLayer::init())
		return false;

	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//当前层的位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCLayerColor* layercolor = CCLayerColor::create(ccc4(0,0,0,150),800,480) ;
	addChild(layercolor);

	ui = TouchGroup::create();
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/challengeLayer.ExportJson"));

	ui->setScale(0.8);
	addChild(ui, 2);

	registerTouchEvent(ui, "resume_challenge", this, ChallengeLayer::buttonClicked) ;
	registerTouchEvent(ui, "backtomain", this, ChallengeLayer::buttonClicked) ;
	registerTouchEvent(ui, "reagain", this, ChallengeLayer::buttonClicked) ;

	//playSound("music/win.ogg");
	::playUIBackgroundMusic();

	UIImageView* pImageNewRecord= imageObj_name(ui, "new_record");
	pImageNewRecord -> setVisible(false);
	Achievement& achi = RunningData::getInstance()->getAchievement();
	int mostTopTimes = achi.getMostTopTimes();
	if(mostTopTimes < repeatTimes)
	{
		achi.setMostTopTimes(repeatTimes);
		achi.save();

		CCActionInterval*  action1 =CCShake::create(0.1,8);
		pImageNewRecord->runAction(action1);
		pImageNewRecord -> setVisible(true);
	}

	UILabel* times = labelObj_name(ui, "challenge_num_1");
	UILabel* top = labelObj_name(ui, "challenge_num_2");
	UILabel* gold = labelObj_name(ui, "challenge_num_3");

	char tem[10];

	sprintf(tem, "%i", repeatTimes);
	times->setText(tem);

	sprintf(tem, "%i", achi.getMostTopTimes());
	top->setText(tem);

	sprintf(tem, "%i", totolGold);
	gold->setText(tem);
	
	return true;
}

void ChallengeLayer::buttonClicked(CCObject *pSender, TouchEventType eType)
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
	case ButtonTagStrenthLevel:
		{
			CCLOG("nextLevel") ;
				CCDirector::sharedDirector()->pushScene(StrengthLevelup::scene());
			//CCDirector::sharedDirector()->replaceScene(BattleManage::scene(m_br.hero,((m_br.level + 1) > 12?12:(m_br.level + 1) ),false));  // 目前只写了三关的数据
		}
		
		break;
	case ButtonTagBackToMain:
		{
			CCLOG("backTomain") ;
			CCDirector::sharedDirector()->replaceScene(GameMainMenu::scene(false));
	
		}
		break;

	case ButtonTagReAgain:
		{
			 CCDirector::sharedDirector()->replaceScene(BattleManage::scene( currentHero,currentLevel,true));
			CCLOG("reagain!");
			
		}
		break;

	default:
		break;
	}
	
}
