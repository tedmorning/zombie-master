#include "StrengthLevelup.h"
#include "tool.h"
#include "TString.h"
#include "data_center\RunningData.h"
#include "shopping_page.h"
#include "ZombieSound.h"
#include "MultiTipsScene.h"
#include "GameMainMenu.h"

enum ButtonTag 
{
	ButtonTagBackToMain = 10,
	ButtonTagLevelUp, //11
	ButtonTagLevelUpToTop, //12
	ButtonTagGetGold,      //13
	ButtonTagJinbiHuiShou,
	ButtonTagFujiaShanghai,
	ButtonTagJisuSheJi,
	ButtonTagGangTieBaoLei,
	ButtonTagNengLiangHuDun,
	ButtonTagSiShenPaoxiao
};

static const int image_tag_operter = 10;

StrengthLevelup::StrengthLevelup()
	:focusTag(ButtonTagJinbiHuiShou)
{}

CCScene* StrengthLevelup::scene()
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	StrengthLevelup *layer = StrengthLevelup::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool StrengthLevelup::init()
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
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/StrengthLevelup.ExportJson"));

	addChild(ui, 2);

	registerTouchEvent(ui, "back", this, StrengthLevelup::buttonClicked) ;
	registerTouchEvent(ui, "levelup", this, StrengthLevelup::buttonClicked) ;
	registerTouchEvent(ui, "leveluptotop", this, StrengthLevelup::buttonClicked) ;
	registerTouchEvent(ui, "getgold", this, StrengthLevelup::buttonClicked) ;
	registerTouchEvent(ui, "jibihuishou", this, StrengthLevelup::buttonClicked) ;
	registerTouchEvent(ui, "fujiashanghai", this, StrengthLevelup::buttonClicked) ;
	registerTouchEvent(ui, "jisusheji", this, StrengthLevelup::buttonClicked) ;
	registerTouchEvent(ui, "gangtiebaolei", this, StrengthLevelup::buttonClicked) ;
	registerTouchEvent(ui, "nenglianghudun", this, StrengthLevelup::buttonClicked) ;
	registerTouchEvent(ui, "sishenpaoxiao", this, StrengthLevelup::buttonClicked) ;

	//初始化等级
	initLevel();
	//显示描述信息
	showDesp();

	if(RunningData::getInstance()->isStrengthLevelupPageTip)
	{
		showFocus(ButtonTagFujiaShanghai);
		scheduleOnce(schedule_selector(StrengthLevelup::showTipMoreDamage),0.1);
	}

	int gold = RunningData::getInstance()->getResource().getGold();
	UILabelAtlas* pLabelNum = labelAtlasObj_name(ui, "AtlasLabel_17");

	char tem[20];
	sprintf(tem,"%i", gold);

	pLabelNum->setStringValue(tem);

	::playUIBackgroundMusic();

	isShowAchievementTip = false;
	schedule(schedule_selector(StrengthLevelup::watch),0.5);
	return true;
}

void StrengthLevelup::showDesp()
{
	Reinfoce& rf = RunningData::getInstance()->getReinfoce();
	int level = rf.m_reinfoceSys[focusTag-ButtonTagJinbiHuiShou].level;
	int maxLevel = rf.m_reinfoceSys[focusTag-ButtonTagJinbiHuiShou].maxLevel;		
	std::string strBenefit;
	std::string strCost;

	if(level == maxLevel)
	{
		strBenefit = rf.m_skillCostRule[focusTag-ButtonTagJinbiHuiShou].costRule[level].despMore;
		strCost = rf.m_skillCostRule[focusTag-ButtonTagJinbiHuiShou].costRule[level].despAddBenefit;
	} else 
	{
		strBenefit = rf.m_skillCostRule[focusTag-ButtonTagJinbiHuiShou].costRule[level].despAddBenefit;
		strCost = rf.m_skillCostRule[focusTag-ButtonTagJinbiHuiShou].costRule[level].despCost;
	}

	UILabel* labelDesp = labelObj_name(ui,"Label_desp");
	UILabel* labelGold = labelObj_name(ui,"Label_gold");
	labelDesp->setText(strBenefit);
	labelGold->setText(strCost);

}

void StrengthLevelup::initLevel()
{
	Reinfoce& rf = RunningData::getInstance()->getReinfoce();

	int curTag = ButtonTagJinbiHuiShou;
	for(int i=0; i< k_reinfoceSysEnd; i++)
	{
		int level = rf.m_reinfoceSys[i].level;
		int maxLevel =  rf.m_reinfoceSys[i].maxLevel;
		int imageTag = curTag*image_tag_operter; //等级图片的tag

		for(int j=0; j<maxLevel; j++)
		{
			imageTag++;
			UIImageView* pImage = imageObj_tag(ui, imageTag);
			if(level > j)
			{
				continue;
			}
			pImage->setVisible(false);
		}
	
		curTag++;		
	}

}

void StrengthLevelup::showFocus(int tag)
{
	focusTag = tag;

	for(int i=ButtonTagJinbiHuiShou; i<=ButtonTagSiShenPaoxiao; i++)
	{
		UIButton* pUIButton = buttonObj_tag(ui, i);

		if (tag == i)
		{
			pUIButton->loadTextures("huang_dikuang.png", "huang_dikuang.png", "", UI_TEX_TYPE_PLIST);

			showDesp();
			
			continue;
		} 
		pUIButton->loadTextures("lan_dikuang.png", "lan_dikuang.png", "", UI_TEX_TYPE_PLIST);
	}

}

void StrengthLevelup::showTipGoBack(float dt)
{
	BattleData& bd = RunningData::getInstance()->getBattleData();
	MultiTipsScene* tips = MultiTipsScene::create();
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(StrengthLevelup::showTipGoBackPoint));
	tips -> setCallFun(func);
	tips -> setTipString(bd.battlePrompt[9].title.c_str());
	addChild(tips,1003);
}

void StrengthLevelup::showTipMoreDamage(float dt)
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	BattleData& bd = RunningData::getInstance()->getBattleData();
	MultiTipsScene* tips = MultiTipsScene::create();
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(StrengthLevelup::showTipMoreDamagePoint));
	tips -> setCallFun(func);
	tips -> setTipString(bd.battlePrompt[8].title.c_str());
	addChild(tips,1003);
}

void StrengthLevelup::showTipMoreDamagePoint()
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	MultiTipsScene* tips = MultiTipsScene::create(ccp(size.width*0.625,size.height*0.23),false,0);
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(StrengthLevelup::moreDamageLevelUp));
	tips -> setCallFun(func);
	addChild(tips,1003);
}

void StrengthLevelup::showTipGoBackPoint()
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();

	MultiTipsScene* tips = MultiTipsScene::create(ccp(size.width*0.917,size.height*0.89),false,0);
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(StrengthLevelup::gotoBattlePage));
	tips -> setCallFun(func);
	addChild(tips,1003);
}

void StrengthLevelup::moreDamageLevelUp()
{
	Resource& res = RunningData::getInstance()->getResource();
	res.addGold(500);

	focusTag = ButtonTagFujiaShanghai;
	levelUpOne();
	showDesp();

	scheduleOnce(schedule_selector(StrengthLevelup::showTipGoBack),0.1);
}

void StrengthLevelup::gotoBattlePage()
{
	RunningData::getInstance()->isStrengthLevelupPageTip = false;
	CCDirector::sharedDirector()->popScene();
}

void StrengthLevelup::levelUpOne()
{
	Reinfoce& rf = RunningData::getInstance()->getReinfoce();
	Resource& res = RunningData::getInstance()->getResource();

	int curIndex = focusTag-ButtonTagJinbiHuiShou;
	int maxLevel = rf.m_reinfoceSys[curIndex].maxLevel;
	int curLevel = rf.m_reinfoceSys[curIndex].level;
	
	if(maxLevel == curLevel) return; //已经满级，则返回

	float value = rf.m_skillCostRule[curIndex].costRule[curLevel].value;
	int costGold = rf.m_skillCostRule[curIndex].costRule[curLevel].cost;
	int ownGold = res.getGold();

	if(costGold > ownGold) //金币不够
	{
		::playSound("music/operationfail.ogg");
		return;
	}

	levelUp(); //升级

	//保存数据
	res.subGold(costGold);
	res.save(); //保存金币数据
	
	rf.m_reinfoceSys[curIndex].level = curLevel + 1;
	rf.m_reinfoceSys[curIndex].value = value;

	rf.serializeReinfoceSys(); //保存技能系统数据

	int gold = res.getGold();
	UILabelAtlas* pLabelNum = labelAtlasObj_name(ui, "AtlasLabel_17");

	char tem[20];
	sprintf(tem,"%i", gold);

	pLabelNum->setStringValue(tem);

	::playSound("music/strengthen.ogg");

	if(rf.m_reinfoceSys[curIndex].level == rf.m_reinfoceSys[curIndex].maxLevel)
	{
		isShowAchievementTip = true;
	}

}

void StrengthLevelup::levelUpMax()
{
	Reinfoce& rf = RunningData::getInstance()->getReinfoce();
	Resource& res = RunningData::getInstance()->getResource();

	int curIndex = focusTag-ButtonTagJinbiHuiShou;
	int maxLevel = rf.m_reinfoceSys[curIndex].maxLevel;
	int curLevel = rf.m_reinfoceSys[curIndex].level;
	
	if(maxLevel == curLevel) return; //已经满级，则返回

	float value = rf.m_skillCostRule[curIndex].costRule[k_level_max].value;
	int costRMB = rf.m_skillCostRule[curIndex].costRule[k_level_max].cost;
	

	//成功回调
	m_successCallback = [=](){
			
			Reinfoce& rf = RunningData::getInstance()->getReinfoce();

			//升级
			levelUp(maxLevel-curLevel);

			//保存数据
	
			rf.m_reinfoceSys[curIndex].level = maxLevel;
			rf.m_reinfoceSys[curIndex].value = value;

			rf.serializeReinfoceSys(); //保存技能系统数据

			isShowAchievementTip = true; //显示成就

			::playSound("music/strengthen.ogg");
			
	};
	m_failCallback = [=](){};


	Shopping& shopping = RunningData::getInstance()->getShopping();
	shopping.setCatalog(k_skill);
	shopping.setIndex(curIndex);

	ShoppingLayer* pShopping = ShoppingLayer::create();
	addChild(pShopping,10);

	pShopping->setSuccessCallFun(m_successCallback);
	pShopping->setFailCallFun(m_failCallback);
}



void StrengthLevelup::levelUp(int num)
{
	Reinfoce& rf = RunningData::getInstance()->getReinfoce();

	int curIndex = focusTag-ButtonTagJinbiHuiShou;
	int level = rf.m_reinfoceSys[curIndex].level;
	int imageTag = focusTag*image_tag_operter + level; //等级图片的tag

	for(int j=level; j<level+num; j++)
	{
		imageTag++;
		UIImageView* pImage = imageObj_tag(ui, imageTag);
		pImage->setVisible(true);	
	}

}

void StrengthLevelup::getGold()
{
		//成功回调

	m_successCallback = [=](){

		Resource& res = RunningData::getInstance()->getResource();
		res.addGold(10000);
		res.save();

		int gold = res.getGold();
		UILabelAtlas* pLabelNum = labelAtlasObj_name(ui, "AtlasLabel_17");

		char tem[20];
		sprintf(tem,"%i", gold);

		pLabelNum->setStringValue(tem);
	};
	m_failCallback = [=](){};

	Shopping& shopping = RunningData::getInstance()->getShopping();
	shopping.setCatalog(k_supply);
	shopping.setIndex(k_getGold);

	ShoppingLayer* pShopping = ShoppingLayer::create();
	addChild(pShopping,10);

	pShopping->setSuccessCallFun(m_successCallback);
	pShopping->setFailCallFun(m_failCallback);

}

void StrengthLevelup::showAchievementTip(int index)
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite* sprite = CCSprite::createWithSpriteFrameName("achievementBg.png");
	char tem[50];
	sprintf(tem, "a%i.png", index);
	CCSprite* spriteFont = CCSprite::createWithSpriteFrameName(tem);
	spriteFont->setPosition(ccp(465,240+160));
	addChild(spriteFont,11);

	sprite->setPosition(ccp(400,240+160));
	addChild(sprite,10);
	sprite->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(4),CCCallFuncN::create(sprite,callfuncN_selector(StrengthLevelup::removeNode))));
	spriteFont->runAction(CCSequence::createWithTwoActions(CCDelayTime::create(4),CCCallFuncN::create(sprite,callfuncN_selector(StrengthLevelup::removeNode))));
	
	Achievement& achi = RunningData::getInstance()->getAchievement();
	achi.achievements[index-1].done = 1;
	achi.save();
}

void StrengthLevelup::removeNode(CCNode* pSender)
{
	pSender->removeFromParent();
}

void StrengthLevelup::watch(float dt)
{
	if(isShowAchievementTip)
	{
		showAchievementTip(focusTag-ButtonTagJinbiHuiShou+4);
		isShowAchievementTip = false;
	}
}

void StrengthLevelup::buttonClicked(CCObject *pSender, TouchEventType eType)
{

	if (eType != TOUCH_EVENT_ENDED)
	{
		return;
	}

	::playSound("music/click.ogg");

	UIButton *button = dynamic_cast<UIButton*>(pSender) ;
	int tag = button->getTag() ;

	//显示焦点
	if(tag >= ButtonTagJinbiHuiShou && tag <= ButtonTagSiShenPaoxiao)
	{
		showFocus(tag);
	}

	switch (tag)
	{
	case ButtonTagBackToMain:
		{
			CCLOG("storyLine mode start!") ;
			if(RunningData::getInstance()->isFromGameMainPage)
			{
				RunningData::getInstance()->isFromGameMainPage=false;
				CCDirector::sharedDirector()->replaceScene(GameMainMenu::scene(false));
			} else 
			{
				CCDirector::sharedDirector()->popScene();
			}
		
		}
		
		break;
	case ButtonTagLevelUp:
		{
			levelUpOne();
			showDesp();
			CCLOG("levelUp mode start!") ;
		}

		break;

	case ButtonTagLevelUpToTop:
		{
			levelUpMax();
			showDesp();
			CCLOG("levelUpToTop start!") ;
		}

		break;
	case ButtonTagJisuSheJi:
		{
			CCLOG("shop mode start!") ;
		}

		break;

	case ButtonTagGetGold:
		{
			getGold();
			CCLOG("getGold()!") ;
			
		}

		break;

		case ButtonTagJinbiHuiShou:
		{
			CCLOG("end game!") ;
			
		}

		break;
		case ButtonTagFujiaShanghai:
		{
			CCLOG("end game!") ;
			
		}

		break;
		case ButtonTagGangTieBaoLei:
		{
			CCLOG("end game!") ;
			
		}

		break;
		case ButtonTagNengLiangHuDun:
		{
			CCLOG("end game!") ;
			
		}

		break;
		case ButtonTagSiShenPaoxiao:
		{
			CCLOG("end game!") ;
			
		}

		break;

	default:
		break;
	}
	
}
