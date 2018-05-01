#include "BattleManage.h"
#include "Map.h"
#include "Enemy.h"
#include "EnemyManage.h"
#include "Firearms.h"
#include "tool.h"
#include "EnemyData.h"
#include "WeaponData.h"
#include "GoldAnimation.h"
#include "PauseLayer.h"
#include "WinLayer.h"
#include "FailLayer.h"
#include "data_center\RunningData.h"
#include "ZombieSound.h"
#include "shopping_page.h"
#include "TipsScene.h"
#include "ChallengeLayer.h"
#include "ChoosePerson.h"
#include "StrengthLevelup.h"
#include "MultiTipsScene.h"
#include "GiftLayer.h"
#include "LuckLayer.h"
#include "BigBoxLayer.h"
CCRenderTexture* BattleManage::s_pRenderTexture = NULL;

enum ButtonTag 
{
	ButtonTagPre = 35,
	ButtonTagNext = 36,     
	ButtonTagBiSha = 34,    
	ButtonTagHuDun = 37,    
	ButtonTagPause = 38    
};


BattleManage* BattleManage::oneself = NULL;

CCScene* BattleManage::scene(int hero,int level,bool repeat)
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	BattleManage *layer = BattleManage::createWithInfo(hero,level,repeat);

	// add layer as a child to scene
	scene->addChild(layer);

	
	// return the scene
	return scene;
}

BattleManage* BattleManage::createWithInfo(int hero,int level,bool repeat)
{
	BattleManage *pRet = new BattleManage();
	pRet -> currentHero = hero;    // 金刚狼 2  黑寡妇 1  变形金刚 3
	pRet -> currentLevel = level;
	pRet -> isrepeatGame = repeat;

	// test
	//pRet -> currentLevel = 6;

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

void BattleManage::onEnter()
{
	CCNode::onEnter() ;
	m_gameover = false;
	this->setTouchEnabled(true);
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void BattleManage::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

void BattleManage::loadImage()
{
	CCLOG("loadImage begin");
	// 根据当前僵尸种类load

	//加载主角图片与plist
	CCTextureCache::sharedTextureCache()->addImage("hero1.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero1.plist");
	CCTextureCache::sharedTextureCache()->addImage("hero2.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero2.plist");
	CCTextureCache::sharedTextureCache()->addImage("hero3.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero3.plist");

	// 加载枪支
	CCTextureCache::sharedTextureCache()->addImage("hero1gun.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero1gun.plist");
	CCTextureCache::sharedTextureCache()->addImage("hero2gun.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero2gun.plist");
	CCTextureCache::sharedTextureCache()->addImage("hero3gun.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero3gun.plist");

	//加载僵尸
	CCTextureCache::sharedTextureCache()->addImage("zombie1.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie1.plist");
	CCTextureCache::sharedTextureCache()->addImage("zombie2.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie2.plist");
	CCTextureCache::sharedTextureCache()->addImage("Zombie3.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Zombie3.plist");
	CCTextureCache::sharedTextureCache()->addImage("zombie4.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie4.plist");
	CCTextureCache::sharedTextureCache()->addImage("zombie5.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie5.plist");
	CCTextureCache::sharedTextureCache()->addImage("zombie6.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie6.plist");
	CCTextureCache::sharedTextureCache()->addImage("zombie7.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie7.plist");
	CCTextureCache::sharedTextureCache()->addImage("zombie8.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie8.plist");
	CCTextureCache::sharedTextureCache()->addImage("zombie9.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie9.plist");
	CCTextureCache::sharedTextureCache()->addImage("zombie10.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie10.plist");
	CCTextureCache::sharedTextureCache()->addImage("zombie11.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie11.plist");
	CCTextureCache::sharedTextureCache()->addImage("zombie12.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie12.plist");

	//if (currentLevel == 12)
	{
		CCTextureCache::sharedTextureCache()->addImage("zombie13_1.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie13_1.plist");
		CCTextureCache::sharedTextureCache()->addImage("zombie13_2.png");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombie13_2.plist");
	}

	// 必杀
	CCTextureCache::sharedTextureCache()->addImage("bisha.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("bisha.plist");

	// 护盾
	CCTextureCache::sharedTextureCache()->addImage("sheild.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("sheild.plist");

	CCLOG("loadImage end");
}

void BattleManage::loadAnimation()
{
	CCLOG("loadAnimation begin");
	///////////////////把帧动画缓冲到内存中//////////////////////////
	for (short k = 0; k < ZombieCount; ++k)
	{
		if (k == ZombieOrdinary || k == ZombieBomb || k == ZombieShield  || k == ZombieMaster|| k == ZombieTyrant || k == ZombieTyrantState2
			|| k == ZombieDoctor || k == ZombieSoldiers  || k == ZombieDog || k == ZombieScholar|| k == ZombieTracker || k == ZombieTrackerState2
			|| k == ZombieGiant  || k == ZombieGeneral || k == ZombieGeneralState2 || k == ZombieBiochemical)
		{ 
			for (int i = 0; i < ZombieAnimationQuantity; i++)
			{
				if (ZombieFrameCount((ZombieType)k, i) != 0)
				{
					CCArray *animaArray = CCArray::createWithCapacity(ZombieFrameCount((ZombieType)k, i));
					for (int j = 1; j <= ZombieFrameCount((ZombieType)k, i); j++)
					{
						CCLOG("ZombieCount:%i, k:%i, ZombieAnimationQuantity:%i, i:%i, ZombieFrameCount((ZombieType)k, i):%i, j:%i",ZombieCount,k,ZombieAnimationQuantity,i,ZombieFrameCount((ZombieType)k, i),j);
						CCSpriteFrame *frame = 
							CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ZombieImageName((ZombieType)k, i, j).data());
						animaArray->addObject(frame);
						CCLOG("J END");
					}
					CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.15f);
					CCLOG("addAnimation begin");
					//把动画缓存起来
					CCAnimationCache::sharedAnimationCache()->addAnimation(animation, AnimationName((ZombieType)k, i).data());
					CCLOG("addAnimation end");
				}
			}
		}
	}
		CCLOG("loadAnimation end");
}

bool BattleManage::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	m_hero_blood = 700 + RunningData::getInstance() ->getReinfoce().m_reinfoceSys[3].value ;
	m_hero_total_blood = m_hero_blood;
	m_sheild_num = 0; // 现在的护盾是无敌状态
	m_sheild_time = 10.0 + RunningData::getInstance() ->getReinfoce().m_reinfoceSys[4].value;
	m_kill_time = 2.0 + RunningData::getInstance() ->getReinfoce().m_reinfoceSys[5].value;
	m_kill_damage = 20;
	getTotalGold = 0;
	killedTotalZombie = 0;
	issheildexit = false;
	iskillingall = false;
	oneself = this;
	showBuyLayer = false;
	sheildExitForever = false;
	isBuyedShowSuccess = false;
	isBuyedShowFail = false;
	isshowingSuccessDelay = false;
	isShowingChengjiu = false;
	isGoFailPage = false;

	CCSprite* fortress = CCSprite::create("battle_fortress.png");
	fortress -> setPosition(ccp(400,0));
	fortress -> setAnchorPoint(ccp(0.5,0.0));
	this -> addChild(fortress,30);

	//管理僵尸的类
	enemyManage = EnemyManage::create(this,currentLevel,isrepeatGame);
	addChild(enemyManage, 1);

	//枪械类
	firearms = Firearms::create();
	firearms->setBattleManage(this);
	BulletType bullettype;
	if (currentHero == 1)
	{
		bullettype = M107;
	}
	else if (currentHero == 2)
	{
		bullettype = RPG_7;
	}
	else
		bullettype = M1014;
	firearms -> setBulletType(bullettype,currentHero);
	addChild(firearms, Bullet_zOrder);

	createSceneAndMap();

	ui = TouchGroup::create();
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/Battle_1.ExportJson"));

	addChild(ui, 1002);
	//触摸有问题，先进入当前Layer的cctouchbegin 一个触摸会分配两次 cocosstudio中能否分配触摸优先级
	//默认触摸优先级为0  可以将当前layer的触摸优先级设低
    registerTouchEvent(ui, "button_pre", this, BattleManage::buttonClicked) ;
	registerTouchEvent(ui, "button_next", this, BattleManage::buttonClicked) ;
	registerTouchEvent(ui, "button_bisha", this, BattleManage::buttonClicked) ;
	registerTouchEvent(ui, "button_hudun", this, BattleManage::buttonClicked) ;
	registerTouchEvent(ui, "button_pause", this, BattleManage::buttonClicked) ;

	bloodbar = loadingBarObj_name(ui,"progress_blood");
	progressbar = loadingBarObj_name(ui,"progress_game");
	UIImageView* progressImage = imageObj_name(ui,"Image_11");
	progressbar -> setPercent(0);
	progressImage -> setPosition(ccp(progressImage -> getPositionX() + 180,progressImage -> getPositionY() - 10));

	if (isrepeatGame)
	{
		progressImage -> setVisible(false);
	}
	else
	{
		progressIcon = CCSprite::create("newUI/progress1.png");
		progressIcon -> setPosition(ccp(progressImage -> getPositionX() - 75,progressImage -> getPositionY() + 10));
		addChild(progressIcon,1002);

		CCArray *animaArray = CCArray::createWithCapacity(3);
		for (int j = 1; j <= 3; j++)
		{
			TString str;
			str += "newUI/progress";
			str += j;
			str += ".png";
			CCSpriteFrame *frame = CCSpriteFrame::create(str.data(),CCRectMake(0,0,51,52));
			animaArray->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.08f);
		CCAnimate* animate = CCAnimate::create(animation);
		progressIcon -> runAction(CCRepeatForever::create(animate));

		CCSprite* bg = CCSprite::create("newUI/bg.png");
		bg -> setPosition(ccp(400,430));
		addChild(bg,1003);
		CCString* name = CCString::createWithFormat("newUI/%d.png",currentLevel);
		CCSprite* level = CCSprite::create(name->getCString());
		level -> setPosition(ccp(400,430));
		addChild(level,1003);
	}
	bloodbar -> setPercent(100);

	bishaWords = CCLayer::create();
	bishaWords -> setVisible(false);
	for (int i = 0;i < 4;i++)
	{
		CCString* tempstring = CCString::createWithFormat("newUI/killallword%d.png",i + 1);
		CCSprite* temp = CCSprite::create(tempstring->getCString());
		temp -> setPosition(ccp(190 + i * 140,240));
		bishaWords -> addChild(temp);
	}
	addChild(bishaWords,1004);

	sheildWords = CCLayer::create();
	sheildWords -> setVisible(false);
	for (int i = 0;i < 4;i++)
	{
			CCLOG("NewUI/sheildword%i.png",i);
		CCString* tempstring = CCString::createWithFormat("newUI/sheildword%d.png",i + 1);
		CCSprite* temp = CCSprite::create(tempstring->getCString());
		temp -> setPosition(ccp(230 + i * 113,240));
		sheildWords -> addChild(temp);
	}
	addChild(sheildWords,1004);

	CCLOG("NewUI/warning00.png");
	//加载所有图片资源
	loadImage();
	//加载帧动画
	loadAnimation();

	warningWord = CCSprite::create("newUI/warning00.png");
	warningWord -> setPosition(ccp(400,240));
	warningWord -> setVisible(false);
	addChild(warningWord,1004);

	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//注册自定义的更新函数
	this->scheduleUpdate();
	this->schedule(SEL_SCHEDULE(&BattleManage::updata));

	//装备数据
	weaponsData = WeaponData::create();
	addChild(weaponsData);

	map = Map::create(this);
	//把map对像加入cocos2dx的内存管理（不需要手动释放）
	this->addChild(map);


	CCLOG("ROLE ANIMATION..");
	//主角动画   主角 关卡信息都要根据传入的来
	if (currentHero != 3)
	{
		TString zhujiaogunname;
		zhujiaogunname += "hero";
		zhujiaogunname += currentHero;
		zhujiaogunname += "_gun1.png";
		zhujiaogun = CCSprite::create();
		zhujiaogun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaogunname.data()));
		float anchorPointY = 20/zhujiaogun -> getContentSize().height;
		zhujiaogun->setAnchorPoint(ccp(0.5f, -anchorPointY));
		zhujiaogun->setPosition(ccp(400, 50));
		addChild(zhujiaogun, 1003);
	}
	else
	{
		TString zhujiaogunname;
		zhujiaogunname += "hero";
		zhujiaogunname += 1;
		zhujiaogunname += "_gun1.png";
		zhujiaogun = CCSprite::create();
		zhujiaogun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaogunname.data()));
		float anchorPointY = 20/zhujiaogun -> getContentSize().height;
		zhujiaogun->setAnchorPoint(ccp(0.5f, -anchorPointY));
		zhujiaogun->setPosition(ccp(400, 50));
		zhujiaogun -> setVisible(false);
		addChild(zhujiaogun, 1003);
	}

	TString zhujiaoname;
	zhujiaoname += "hero";
	zhujiaoname += currentHero;
	zhujiaoname += "_middle1.png";
	zhujiao = CCSprite::create();
	zhujiao->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaoname.data()));
	zhujiao->setAnchorPoint(ccp(0.5f, 0.0f));
	zhujiao->setPosition(ccp(400, 30));  // ccp(400,30)  人物、枪旋转的中心点
	//zhujiao -> setVisible(false);
	addChild(zhujiao, 1004);

	TString zhujiaolegname;
	zhujiaolegname += "hero";
	zhujiaolegname += currentHero;
	zhujiaolegname += "_middleleg.png";
	zhujiaoleg = CCSprite::createWithSpriteFrameName(zhujiaolegname.data());
	zhujiaoleg -> setPosition(ccp(400, 15));
	zhujiaoleg->setAnchorPoint(ccp(0.5f, 0.0f));
	//zhujiaoleg -> setVisible(false);
	addChild(zhujiaoleg,1002);
	moveZhujiao(90.0);

	CCLOG("ROLE HEAD..");
	//主角头像
	TString heroiconname;
	heroiconname += "hero";
	heroiconname += currentHero;
	heroiconname += "_icon.png";
	heroicon = CCSprite::createWithSpriteFrameName(heroiconname.data());
	heroicon -> setPosition(ccp(75,428));
	addChild(heroicon,1002);

	CCSprite* iconTop = CCSprite::create("heroicontop.png");
	iconTop -> setPosition(ccp(75,428));
	addChild(iconTop,1002);

	CCSprite* killalltop = CCSprite::create("killallbuttontop.png");
	killalltop -> setPosition(ccp(115,40));
	addChild(killalltop,1002);

	CCSprite* sheildtop = CCSprite::create("killallbuttontop.png");
	sheildtop -> setPosition(ccp(680,40));
	addChild(sheildtop,1002);

	heroiconLeft = CCSprite::create("hero1clickicon.png");
	heroiconLeft -> setPosition(ccp(290,27));
	addChild(heroiconLeft,1002);

	heroiconRight = CCSprite::create("hero3clickicon.png");
	heroiconRight -> setPosition(ccp(527,27));
	addChild(heroiconRight,1002);

	TString killallstring;
	killallstring += "*";
	int killnum = RunningData::getInstance() ->getResource().getUniqueKillNum();
	killallstring += killnum;
	killallNum = CCLabelTTF::create(killallstring.data(),"Arial",20);
	killallNum -> setPosition(ccp(135,15));
	this -> addChild(killallNum,1002);

	TString sheildstring;
	sheildstring += "*";
	int sheildnum = RunningData::getInstance() ->getResource().getShieldNum();
	sheildstring += sheildnum;
	sheildNum = CCLabelTTF::create(sheildstring.data(),"Arial",20);
	sheildNum -> setPosition(ccp(695,15));
	this -> addChild(sheildNum,1002);
	CCLOG("changeHero(0)");
	changeHero(0);

		
// 
// 	if (currentLevel != 1 && (!CCUserDefault::sharedUserDefault()->getBoolForKey("vip", false)))
// 	{
// 		GiftLayer * layer = GiftLayer::create(VIP);
// 		addChild(layer, 1101);
// 	}

	return true;
}

void BattleManage::createSceneAndMap()
{
	//currentLevel = 9;

	playBackgroundMusic("music/game1.mp3", true);
	CCSprite* bg = CCSprite::create("battle_bg.jpg");
	bg->setPosition(ccp(400, 240));
	addChild(bg);
	
	CCSprite* leftboard = CCSprite::create("left_billboard.png");
	leftboard->setPosition(ccp(165, 438));
	this->addChild(leftboard, 1);
	
	CCSprite* leftbuild = CCSprite::create("left_building.png");
	leftbuild->setPosition(ccp(70, 240));
	this->addChild(leftbuild, 0);
	
	CCSprite* rightboard = CCSprite::create("right_billboard.png");
	rightboard->setPosition(ccp(615, 438));
	this->addChild(rightboard, 1);
	
	CCSprite* rightbuild = CCSprite::create("right_building.png");
	rightbuild->setPosition(ccp(730, 240));
	this->addChild(rightbuild, 0);
	
	CCSprite* bgup = CCSprite::create("battle_up_bg.png");
	bgup->setPosition(ccp(400, 240));
	this->addChild(bgup, 32);
	
	//僵尸数据   地图数据
	int datalevel = currentLevel > 12 ? 12 : currentLevel;
	data = EnemyData::createWithID(datalevel);



	/*
	if (!isrepeatGame)
	{

	
		if (currentLevel <= 4 && currentLevel > 0) 
		{
			playBackgroundMusic("music/game1.mp3",true);
			CCSprite* bg = CCSprite::create("battle_bg.jpg") ;
			bg->setPosition(ccp(400,240));
			addChild(bg) ;

			CCSprite* leftboard = CCSprite::create("left_billboard.png");
			leftboard -> setPosition(ccp(165,438));
			this -> addChild(leftboard,1);

			CCSprite* leftbuild = CCSprite::create("left_building.png");
			leftbuild -> setPosition(ccp(70,240));
			this -> addChild(leftbuild,0);

			CCSprite* rightboard = CCSprite::create("right_billboard.png");
			rightboard -> setPosition(ccp(615,438));
			this -> addChild(rightboard,1);

			CCSprite* rightbuild = CCSprite::create("right_building.png");
			rightbuild -> setPosition(ccp(730,240));
			this -> addChild(rightbuild,0);

			CCSprite* bgup = CCSprite::create("battle_up_bg.png");
			bgup -> setPosition(ccp(400,240));
			this -> addChild(bgup,32);

			//僵尸数据   地图数据
			data = EnemyData::createWithID(currentLevel);
		}
		else if (currentLevel > 4 && currentLevel <= 8)
		{
			playBackgroundMusic("music/game2.mp3",true);
			//僵尸数据   地图数据
			data = EnemyData::createWithID(currentLevel);
			CCSprite* bg = CCSprite::create("battle_bg2.jpg") ;
			bg->setPosition(ccp(400,240));
			addChild(bg) ;

			CCSprite* fortress = CCSprite::create("bg2door.png");
			fortress -> setPosition(ccp(400,480));
			fortress -> setAnchorPoint(ccp(0.5,1.0));
			this -> addChild(fortress,30);

			CCSprite* leftboard = CCSprite::create("bg2stone1.png");
			leftboard -> setPosition(ccp(303,305));
			this -> addChild(leftboard,0);

			CCSprite* leftbuild = CCSprite::create("bg2stone2.png");
			leftbuild -> setAnchorPoint(ccp(0.0,0.5));
			leftbuild -> setPosition(ccp(0,324));
			this -> addChild(leftbuild,30);

			CCSprite* rightboard = CCSprite::create("bg2tree.png");
			rightboard -> setAnchorPoint(ccp(1.0,0.5));
			rightboard -> setPosition(ccp(815,315));
			this -> addChild(rightboard,30);

			CCSprite* rightbuild = CCSprite::create("bg2head.png");
			rightbuild -> setPosition(ccp(576,190));
			this -> addChild(rightbuild);

			firearms -> createCollisionRect(1);
		}
		else if (currentLevel > 8 && currentLevel <= 12)
		{
			playBackgroundMusic("music/game3.mp3",true);
			//僵尸数据   地图数据
			data = EnemyData::createWithID(currentLevel);
			CCSprite* bg = CCSprite::create("battle_bg3.jpg") ;
			bg->setPosition(ccp(400,240));
			addChild(bg) ;

			CCSprite* bgup = CCSprite::create("bg3warning.png");
			bgup -> setAnchorPoint(ccp(0.5,1.0));
			bgup -> setPosition(ccp(400,480));
			this -> addChild(bgup);

			CCSprite* fortress = CCSprite::create("bg3barrel.png");
			fortress -> setPosition(ccp(158,145));
			this -> addChild(fortress,30);

			CCSprite* leftboard = CCSprite::create("bg3door.png");
			leftboard -> setAnchorPoint(ccp(0.5,1.0));
			leftboard -> setPosition(ccp(400,480));
			this -> addChild(leftboard,30);

			CCSprite* leftbuild = CCSprite::create("bg3exit.png");
			leftbuild -> setAnchorPoint(ccp(0.0,1.0));
			leftbuild -> setPosition(ccp(0,480));
			this -> addChild(leftbuild,30);
			firearms -> createCollisionRect(2);
		}
	}
	else
	{
		playBackgroundMusic("music/game3.mp3",true);
		//僵尸数据   地图数据
		data = EnemyData::createWithID(10,true);
		CCSprite* bg = CCSprite::create("battle_bg3.jpg") ;
		bg->setPosition(ccp(400,240));
		addChild(bg) ;

		CCSprite* bgup = CCSprite::create("bg3warning.png");
		bgup -> setAnchorPoint(ccp(0.5,1.0));
		bgup -> setPosition(ccp(400,480));
		this -> addChild(bgup);

		CCSprite* fortress = CCSprite::create("bg3barrel.png");
		fortress -> setPosition(ccp(158,145));
		this -> addChild(fortress,30);

		CCSprite* leftboard = CCSprite::create("bg3door.png");
		leftboard -> setAnchorPoint(ccp(0.5,1.0));
		leftboard -> setPosition(ccp(400,480));
		this -> addChild(leftboard,30);

		CCSprite* leftbuild = CCSprite::create("bg3exit.png");
		leftbuild -> setAnchorPoint(ccp(0.0,1.0));
		leftbuild -> setPosition(ccp(0,480));
		this -> addChild(leftbuild,30);
		firearms -> createCollisionRect(2);
	}
	*/

	//把数据类托管到cocos2dx的内存管理中
	addChild(data); 
}

void BattleManage::moveZhujiao(float degree,bool repeat)
{
	if (currentHero != 1 && currentHero != 2 && currentHero != 3)
	{
		return;
	}
	// 1-5  最左 左 中 右 最右
	int type = degree / 36.0 + 1;
	float rorationdegree = (degree - (type - 1) * 36) - 18;

	if (currentHero == 3 && type == 1)
	{
		rorationdegree -= 36;
	}
	else if (currentHero == 3 && type == 5)
	{
		rorationdegree += 36;
	}

	float gunroration  = degree - 90;
	if (type != zhujiaoactionindex || repeat)
	{
		TString strleg;
		CCArray *animaArray = CCArray::createWithCapacity(4);
		for (int j = 1; j <= 3; j++)
		{
			TString str;
			TString strtemp;
			switch (type)
			{
			case 1:
				{
					str += "hero";
					str += currentHero;
					str += "_Lleft";
					strtemp 	+= "hero";
					strtemp += currentHero;
					strtemp += "_Lleft";
				}
				break;
			case 2:
				{
					str += "hero";
					str += currentHero;
					str += "_left";
					strtemp += "hero";
					strtemp += currentHero;
					strtemp += "_left";
				}
				break;
			case 3:
				{
					str += "hero";
					str += currentHero;
					str += "_middle";
					strtemp += "hero";
					strtemp += currentHero;
					strtemp += "_middle";
				}
				break;
			case 4:
				{
					str += "hero";
					str += currentHero;
					str += "_right";
					strtemp += "hero";
					strtemp += currentHero;
					strtemp += "_right";
				}
				break;
			case 5:
				{
					str += "hero";
					str += currentHero;
					str += "_Rright";
					strtemp += "hero";
					strtemp += currentHero;
					strtemp += "_Rright";
				}
				break;
			default:
				{
					str += "hero";
					str += currentHero;
					str += "_Lleft";
					strtemp 	+= "hero";
					strtemp += currentHero;
					strtemp += "_Lleft";
				}
				break;
			}
			strleg = strtemp;
			str += j;
			str += ".png";
			CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		strleg += "leg.png";
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.3);
		CCAnimate* animate = CCAnimate::create(animation);
		zhujiao -> stopAllActions();
		zhujiao -> runAction(CCRepeatForever::create(animate));
		zhujiaoleg -> setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(strleg.data()));
		zhujiaoactionindex = type;
	}
	if (currentHero != 3)
	{
		zhujiaogun -> setVisible(true);
		zhujiaogun -> setRotation(gunroration);
	}
	zhujiao -> setRotation(rorationdegree);
}

void BattleManage::updata(float dt)
{

	TString killallstring;
	killallstring += "*";
	int killnum = RunningData::getInstance() ->getResource().getUniqueKillNum();
	killallstring += killnum;
	killallNum -> setString(killallstring.data());

	TString sheildstring;
	sheildstring += "*";
	int sheildnum = RunningData::getInstance() ->getResource().getShieldNum();
	sheildstring += sheildnum;
	sheildNum -> setString(sheildstring.data());

	checkshowchengjiu();
	if (!isShowingChengjiu)  // 展示成就的几秒内  不显示成功失败界面！
	{
		//更新函数，每一帧都进来一次
		if (!isrepeatGame)
		{
			if(isBuyedShowSuccess)
			{
				isBuyedShowSuccess = false;
				showWinLayer(true);
				pauseSchedulerAndActions();
				return;
			}
			if(isBuyedShowFail)
			{
				isBuyedShowFail = false;
				showWinLayer(false);
				pauseSchedulerAndActions();
				return;

			}
			if(isGoFailPage)
			{
				isGoFailPage = false;
				addChild(FailLayer::create(currentHero,currentLevel), 1005);
				pauseSchedulerAndActions();
				return;
			}
			if (enemyManage -> buildZombieFinished && enemyManage -> getEnemySize() < 1) {// 成功

				if(issheildexit)
				{
					removeSheildEffect(0);
				}

				//if (currentLevel == 1 && !showBuyLayer)
				//{
				//	//showTipsSix(0.0);
				//	showWinLayer(true);
				//	showBuyLayer = true;
				//	return;
				//}
				//else 
				


				if(!showBuyLayer && currentLevel == 12 && !isshowingSuccessDelay)
				{
					isshowingSuccessDelay = true;
					BattleData& bd = RunningData::getInstance()->getBattleData();
					CCLOG("output%s",bd.battlePrompt[6].title.c_str());
					overGameTips = CCLabelTTF::create(bd.battlePrompt[6].title.c_str(),"Arial",40);
					overGameTips -> setColor(ccYELLOW);
					overGameTips ->setPosition(ccp(400,240));
					addChild(overGameTips,2000);
					scheduleOnce(schedule_selector(BattleManage::showSuccessDelay),3.0f);
					return;
				}
				else if (!showBuyLayer && !isshowingSuccessDelay)
				{
					showWinLayer(true);
					return;
				}
			}
			else if (m_hero_blood <= 0)  // 失败 
			{
				if(issheildexit)
				{
					removeSheildEffect(0);
				}
				
				if(RunningData::getInstance()->isFromStrengthLevelupPage) 
				{
					RunningData::getInstance()->isFromStrengthLevelupPage = false;
					pauseSchedulerAndActions();
					return;
				}

				if (CCUserDefault::sharedUserDefault()->getIntegerForKey("fuhuo", 1) > 0)
				{
					CCUserDefault::sharedUserDefault()->setIntegerForKey("fuhuo", CCUserDefault::sharedUserDefault()->getIntegerForKey("fuhuo", 0) - 1);

					m_hero_blood = 1000 + RunningData::getInstance()->getReinfoce().m_reinfoceSys[3].value;
					m_hero_total_blood = m_hero_blood;
					bloodbar->setPercent(100);
					resumeSchedulerAndActions();

					//添加满血复活的提示
// 					CCLabelTTF * label = CCLabelTTF::create();
// 					this->addChild(label, 1000);
// 					label->setPosition(ccp(400,240));
// 					label->setString(_text("reblood"));
// 					label->setFontSize(50);
// 					label->runAction(CCSequence::create(CCFadeOut::create(2),CCRemoveSelf::create(),NULL));

					CCSprite * sp = CCSprite::create("giftlayer/revivefree.png");
					sp->setPosition(ccp(800, 240));
					sp->runAction(CCSequence::create(CCMoveTo::create(0.5,ccp(400,240)),CCRemoveSelf::create(),NULL));

					return;
				}


				//立即复活回调
				m_successCallback = [=](){
					Resource& resource = RunningData::getInstance()->getResource();

					resource.addShield(1);
					resource.save(); //保存
				
					m_hero_blood = 1000 + RunningData::getInstance() ->getReinfoce().m_reinfoceSys[3].value ;
					m_hero_total_blood = m_hero_blood;
					bloodbar -> setPercent(100);

					resumeSchedulerAndActions();
				};

				m_failCallback = [=](){
					isGoFailPage = true;
					resumeSchedulerAndActions();
				};
				//复活礼包回调

				std::function<void()> m_successCallbackGif = [=](){
					Resource& resource = RunningData::getInstance()->getResource();
					resource.addUniqueKill(5);
					resource.addShield(5);
					resource.save(); //保存

					CCUserDefault::sharedUserDefault()->setIntegerForKey("fuhuo", CCUserDefault::sharedUserDefault()->getIntegerForKey("fuhuo", 0)+5);
					m_hero_blood = 1000 + RunningData::getInstance()->getReinfoce().m_reinfoceSys[3].value;
					m_hero_total_blood = m_hero_blood;
					bloodbar->setPercent(100);

					resumeSchedulerAndActions();
				};



				//礼包失败回调
				std::function<void()>  m_failCallbackGift = [=](){
					

					Shopping& shopping = RunningData::getInstance()->getShopping();
					shopping.setCatalog(k_supply);
					shopping.setIndex(k_rebirth);
					ShoppingLayer* pShopping = ShoppingLayer::create();
					addChild(pShopping, 1005);
					pShopping->setSuccessCallFun(m_successCallback);
					pShopping->setFailCallFun(m_failCallback);
				};

			
				GiftLayer * giftLayer = GiftLayer::create(k_pay_revievegift);

				giftLayer->setSuccessCallFun(m_successCallbackGif);
				giftLayer->setFailCallFun(m_failCallbackGift);
				this->addChild(giftLayer,100);


				pauseSchedulerAndActions();
			
				return;
			}
		} 
		else 
		{
			if (m_hero_blood <= 0)  // 失败 
			{
				// 传入EnemyData::data -> repeatTimes   这个就是保存当前无限关卡波次的    记得清零
				int repeatTimes = EnemyData::data -> repeatTimes;
				int perGold = CCRANDOM_0_1()*3 + 8;

				int totolGold = repeatTimes*perGold;
				//保存金币
				Resource& resource = RunningData::getInstance()->getResource();
				resource.addGold(totolGold);
				resource.save();

				if(issheildexit)
				{
					removeSheildEffect(0);
				}

				CCScene* pScene = CCScene::create();
				CCSprite* pBackground = CCSprite::createWithTexture(getScreenCapture(true)->getSprite()->getTexture());
				pBackground->setPosition(ccp(400.0, 240.0));
				pBackground->setFlipY(true);
				pScene->addChild(pBackground);

				pScene->addChild(ChallengeLayer::create(currentHero,currentLevel, repeatTimes, totolGold));

				CCDirector::sharedDirector()->replaceScene(pScene);
			}
		}
	}
    
	enemyManage->updata(dt);
	firearms->updata(dt);
}

void BattleManage::checkshowchengjiu()
{
	if (isShowingChengjiu)
	{
		return;
	}
	if (enemyManage -> buildZombieFinished && enemyManage -> getEnemySize() < 1)
	{
		bool isFirstPlay12 = CCUserDefault::sharedUserDefault()-> getBoolForKey("firstplay12",false);
		bool isFirstPlay1 = CCUserDefault::sharedUserDefault()-> getBoolForKey("firstplay1",false);
		bool isFirstPlay6 = CCUserDefault::sharedUserDefault()-> getBoolForKey("firstplay6",false);
		// 第一次显示成就
		if (currentLevel == 1 && !isFirstPlay1)
		{
			Achievement& achieve = RunningData::getInstance() ->getAchievement();
			achieve.achievements[0].done =1;
			achieve.save();
			isShowingChengjiu = true;
			CCUserDefault::sharedUserDefault()-> setBoolForKey("firstplay1",true);
			scheduleOnce(schedule_selector(BattleManage::scheduleCouldShowSuccess),5.0f);
			
			showChengjiuBG = CCSprite::createWithSpriteFrameName("achievementBg.png");
			showChengjiuBG -> setPosition(ccp(400,300));
			addChild(showChengjiuBG,1003);
			showChengjiuTop = CCSprite::createWithSpriteFrameName("a1.png");
			showChengjiuTop -> setPosition(ccp(465,300));
			addChild(showChengjiuTop,1003);
		}
		else if (currentLevel == 6 && !isFirstPlay6)
		{
			Achievement& achieve = RunningData::getInstance() ->getAchievement();
			achieve.achievements[1].done =1;
			achieve.save();
			isShowingChengjiu = true;
			scheduleOnce(schedule_selector(BattleManage::scheduleCouldShowSuccess),5.0f);
			CCUserDefault::sharedUserDefault()-> setBoolForKey("firstplay6",true);
			showChengjiuBG = CCSprite::createWithSpriteFrameName("achievementBg.png");
			showChengjiuBG -> setPosition(ccp(400,300));
			addChild(showChengjiuBG,1003);
			showChengjiuTop = CCSprite::createWithSpriteFrameName("a2.png");
			showChengjiuTop -> setPosition(ccp(465,300));
			addChild(showChengjiuTop,1003);
		}
		else if (currentLevel == 12 && !isFirstPlay12)
		{
			Achievement& achieve = RunningData::getInstance() ->getAchievement();
			achieve.achievements[2].done =1;
			achieve.save();
			isShowingChengjiu = true;
			CCUserDefault::sharedUserDefault()-> setBoolForKey("firstplay12",true);
			scheduleOnce(schedule_selector(BattleManage::scheduleCouldShowSuccess),5.0f);

			showChengjiuBG = CCSprite::createWithSpriteFrameName("achievementBg.png");
			showChengjiuBG -> setPosition(ccp(400,300));
			addChild(showChengjiuBG,1003);
			showChengjiuTop = CCSprite::createWithSpriteFrameName("a3.png");
			showChengjiuTop -> setPosition(ccp(465,300));
			addChild(showChengjiuTop,1003);
		}
	}
	else
	{
		bool sheildAchieve = CCUserDefault::sharedUserDefault()-> getBoolForKey("sheildAchieve",false);
		bool killAchieve = CCUserDefault::sharedUserDefault()-> getBoolForKey("killAchieve",false);
		Achievement& achieve = RunningData::getInstance() ->getAchievement();
		if (achieve.getShieldNumTimes() >= 4 && !sheildAchieve)
		{
			Achievement& achieve = RunningData::getInstance() ->getAchievement();
			achieve.achievements[10].done =1;
			achieve.save();
			CCUserDefault::sharedUserDefault()-> setBoolForKey("sheildAchieve",true);

			isShowingChengjiu = true;
			scheduleOnce(schedule_selector(BattleManage::scheduleCouldShowSuccess),4.0f);

			showChengjiuBG = CCSprite::createWithSpriteFrameName("achievementBg.png");
			showChengjiuBG -> setPosition(ccp(400,300));
			addChild(showChengjiuBG,1003);
			showChengjiuTop = CCSprite::createWithSpriteFrameName("a11.png");
			showChengjiuTop -> setPosition(ccp(465,300));
			addChild(showChengjiuTop,1003);
		}
		if (achieve.getUniqueKillNumTimes() >= 4 && !killAchieve)
		{
			CCUserDefault::sharedUserDefault()-> setBoolForKey("killAchieve",true);
			Achievement& achieve = RunningData::getInstance() ->getAchievement();
			achieve.achievements[9].done =1;
			achieve.save();
			isShowingChengjiu = true;
			scheduleOnce(schedule_selector(BattleManage::scheduleCouldShowSuccess),4.0f);

			showChengjiuBG = CCSprite::createWithSpriteFrameName("a10.png");
			showChengjiuBG -> setPosition(ccp(400,300));
			addChild(showChengjiuBG,1003);
			showChengjiuTop = CCSprite::createWithSpriteFrameName("achievementBg.png");
			showChengjiuTop -> setPosition(ccp(465,300));
			addChild(showChengjiuTop,1003);
		}
	}
}

void BattleManage::scheduleCouldShowSuccess(float dt)
{
	showChengjiuBG -> removeFromParent();
	showChengjiuTop -> removeFromParent();
	isShowingChengjiu = false;
}

void BattleManage::showSuccessDelay(float dt)
{
	overGameTips -> removeFromParent();
	showWinLayer(true);
}
void BattleManage::showWinLayer(bool issuccess)
{/*
	CCScene* pScene = CCScene::create();

	CCSprite* pBackground = CCSprite::createWithTexture(getScreenCapture(true)->getSprite()->getTexture());
	pBackground->setPosition(ccp(400.0, 240.0));
	pBackground->setFlipY(true);
	pScene->addChild(pBackground);

	CCLOG("winlayer1 ");
	*/
	

	int randomGold = CCRANDOM_0_1()*40 + 510;

	GameLevel& gl = RunningData::getInstance()->getGameLevel();
	if(getChildByTag(111111))
		return;

	BattleResult br;
	br.hero = currentHero;
	br.level = currentLevel;
	br.getGoldNum = randomGold;
	br.killedZombieNum = killedTotalZombie;
	br.remainBlood = m_hero_blood/m_hero_total_blood * 100;
	//pScene->addChild(WinLayer::create(br));

	//添加vip

	

	if (gl.getStage() == 1)
	{
		//CCUserDefault::sharedUserDefault()->getIntegerForKey();
// 		luckLayer->setVisible(false);
		std::function<void()> m_callBack = [=]()
		{
			addChild(WinLayer::create(br), 1002, 111111);

			//添加抽奖的Layer
			LuckLayer * luckLayer = LuckLayer::create();

			addChild(luckLayer, 1100);
		};

// 		if (!CCUserDefault::sharedUserDefault()->getBoolForKey("vip", false))
// 		{
// 			GiftLayer * layer = GiftLayer::create(VIP);
// 			addChild(layer, 1101);
// 			layer->setFailCallFun(m_callBack);
// 			layer->setSuccessCallFun(m_callBack);
// 		}
		BigBoxLayer * boxLayer = BigBoxLayer::create();
		boxLayer->setCallFun(m_callBack);
		addChild(boxLayer,100);
		
	}
	else
	{
		addChild(WinLayer::create(br), 1002, 111111);

		//添加抽奖的Layer
		LuckLayer * luckLayer = LuckLayer::create();

		addChild(luckLayer, 1100);

	}


// 	if(gl.getStage() == 1)
// 	{
// 		//强化引导
// 		showTipsInstensigy(0);
// 	}

	//保存金币
	Resource& resource = RunningData::getInstance()->getResource();
	resource.addGold(randomGold);
	resource.save();

	//总共杀死僵尸数目
	Achievement& achi = RunningData::getInstance()->getAchievement();
	achi.setKilledZombieNumber(achi.getKilledZombieNumber() + killedTotalZombie);
	achi.save();

	if(issuccess)
	{
		//保存关卡数据
		//GameLevel& gl = RunningData::getInstance()->getGameLevel();
		LevelInfo& li = gl.getCurrentLevelInfo();
		gl.addStage();
		li.rating = 2;

		gl.saveLevelInfo();
	}


	CCLOG("winlayer3");
	//CCDirector::sharedDirector()->replaceScene(pScene);

}

void BattleManage::fireGunAnimation()
{
	if (currentHero == 2)
	{
		CCArray *animaArray = CCArray::createWithCapacity(3);
		for (int j = 1; j <= 3; j++)
		{
			TString str;
			str += "hero2_gun1";
			str += j;
			str += ".png";
			CCSpriteFrame *frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		CCSpriteFrame *frame = 
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2_gun1.png");
		animaArray->addObject(frame);
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
		CCAnimate* animate = CCAnimate::create(animation);
		zhujiaogun -> runAction(animate);
	}
}

void BattleManage::changeHero(int direct)
{
	// 暂时只有两个英雄 两个切换  // // 金刚狼 2  黑寡妇 1  变形金刚 3
	heroTemp = currentHero;
	heroTemp += direct;
	if (heroTemp < 1)
	{
		heroTemp = 3;
	}
	else if (heroTemp > 3)
	{
		heroTemp = 1;
	}

	if (heroTemp == 1)
	{
		RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
		Role& role = rs.m_roleInfos[1];
		if (role.available != 1)
		{

			//成功回调
			m_successCallback = [=](){
				resumeSchedulerAndActions();
// 				RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
// 				Role& role = rs.m_roleInfos[1];
// 				role.available = 1; //角色可用
// 				rs.serializeRole(); //保存到本地

			};

			//失败回调
			m_failCallback = [=](){
				resumeSchedulerAndActions();
			};

			// 购买黑寡妇
			Shopping& shopping = RunningData::getInstance()->getShopping();
			shopping.setCatalog(2);
			shopping.setIndex(1);


			GiftLayer * gift = GiftLayer::create(k_pay_newgift);
			addChild(gift, 1005);
			gift->setSuccessCallFun(m_successCallback);
			gift->setFailCallFun(m_failCallback);
// 			ShoppingLayer* pShopping = ShoppingLayer::create();
// 			addChild(pShopping,1005);
// 			pShopping->setSuccessCallFun(m_successCallback);
// 			pShopping -> setFailCallFun(m_failCallback);


			pauseSchedulerAndActions();
			return;
		}

		heroiconLeft -> removeFromParent();
		heroiconRight -> removeFromParent();

		heroiconLeft = CCSprite::create("hero3clickicon.png");
		heroiconLeft -> setPosition(ccp(290,27));
		addChild(heroiconLeft,1002);
		    
		heroiconRight = CCSprite::create("hero2clickicon.png");
		heroiconRight -> setPosition(ccp(527,27));
		addChild(heroiconRight,1002);
	}
	else if (heroTemp == 2)
	{
		heroiconLeft -> removeFromParent();
		heroiconRight -> removeFromParent();

		heroiconLeft = CCSprite::create("hero1clickicon.png");
		heroiconLeft -> setPosition(ccp(290,27));
		addChild(heroiconLeft,1002);

		heroiconRight = CCSprite::create("hero3clickicon.png");
		heroiconRight -> setPosition(ccp(527,27));
		addChild(heroiconRight,1002);
	}
	else  
	{
		RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
		Role& role = rs.m_roleInfos[2];
		if (role.available != 1)
		{
			//成功回调
			m_successCallback = [=](){
				resumeSchedulerAndActions();
// 				RoleSystem& rs = RunningData::getInstance()->getRoleSystem();
// 				Role& role = rs.m_roleInfos[2];
// 				role.available = 1; //角色可用
// 				rs.serializeRole(); //保存到本地

			};

			//失败回调
			m_failCallback = [=](){
				resumeSchedulerAndActions();
			};

			// 购买黑寡妇
			Shopping& shopping = RunningData::getInstance()->getShopping();
			shopping.setCatalog(2);
			shopping.setIndex(k_ironmen);

			GiftLayer * gift = GiftLayer::create(k_pay_supergift);
			addChild(gift, 1005);
			gift->setSuccessCallFun(m_successCallback);
			gift->setFailCallFun(m_failCallback);
// 			ShoppingLayer* pShopping = ShoppingLayer::create();
// 			addChild(pShopping,1005);
// 			pShopping->setSuccessCallFun(m_successCallback);
// 			pShopping -> setFailCallFun(m_failCallback);
			pauseSchedulerAndActions();
			return;
		}

		heroiconLeft -> removeFromParent();
		heroiconRight -> removeFromParent();

		heroiconLeft = CCSprite::create("hero2clickicon.png");
		heroiconLeft -> setPosition(ccp(290,27));
		addChild(heroiconLeft,1002);

		heroiconRight = CCSprite::create("hero1clickicon.png");
		heroiconRight -> setPosition(ccp(527,27));
		addChild(heroiconRight,1002);
	}

	CCLOG("	currentHero = heroTemp;");
	currentHero = heroTemp;

	TString zhujiaoname;
	zhujiaoname += "hero";
	zhujiaoname += currentHero;
	zhujiaoname += "_middle1.png";
	zhujiao->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaoname.data()));

	TString zhujiaolegname;
	zhujiaolegname += "hero";
	zhujiaolegname += currentHero;
	zhujiaolegname += "_middleleg.png";
	zhujiaoleg -> setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaolegname.data()));
	moveZhujiao(90,true);

	CCLOG("TString heroiconname;;");
	//主角头像
	TString heroiconname;
	heroiconname += "hero";
	heroiconname += currentHero;
	heroiconname += "_icon.png";
	heroicon -> setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(heroiconname.data()));

	if (currentHero != 3)
	{
		TString zhujiaogunname;
		zhujiaogunname += "hero";
		zhujiaogunname += currentHero;
		zhujiaogunname += "_gun1.png";
		zhujiaogun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaogunname.data()));

		zhujiaogun -> setVisible(true);
		zhujiao->setPosition(ccp(400, 30));
	}
	else
	{
		zhujiaogun -> setVisible(false);
		zhujiao->setPosition(ccp(400, 0));
		zhujiaoleg -> setPosition(ccp(400,0));
	}

	switch(currentHero)
	{
	case 1:
		{
			firearms -> setBulletType(M107,currentHero);
		}
		break;
	case 2:
		{
			firearms -> setBulletType(RPG_7,currentHero);
		}
		break;
	case 3:
		{
			firearms -> setBulletType(M1014,currentHero);
		}
		break;
	}
	CCLOG("changeHero end;");
}

void BattleManage::changeHeroBlood(int changeValue)
{
	if (changeValue > 0)
	{
		m_hero_blood += changeValue;
	}
	else
	{
		// 修改进度条  修改护盾
		if (!issheildexit)
		{
			m_hero_blood += changeValue;
			bloodbar -> setPercent(m_hero_blood/m_hero_total_blood *100);
		}
	}
}

void BattleManage::setProgressBar(int percent)
{
	static CCPoint pos = progressIcon -> getPosition();
	progressIcon -> setPosition(ccp(pos.x+ 155 * (percent/100.0f),pos.y));
	progressbar -> setPercent(percent); 
}

void BattleManage::buildGold(short number, CCPoint point)
{
	GoldAnimation *gold = GoldAnimation::create();
	gold->setGoldQuantity(number);
	gold->setPosition(point);
	addChild(gold, Gold_zOrder);
}

void BattleManage::buttonClicked(CCObject *pSender, TouchEventType eType)
{
	if (eType != TOUCH_EVENT_ENDED)
	{
		return;
	}

	UIButton *button = dynamic_cast<UIButton*>(pSender) ;
	int tag = button->getTag() ;

	switch (tag)
	{
	case ButtonTagPre:
		{
			playSound("music/click.ogg");
			changeHero(-1);
		}
		break;
	case ButtonTagNext:
		{
			playSound("music/click.ogg");
			changeHero(1);
		}

		break;

	case ButtonTagBiSha:
		{
			if (!RunningData::getInstance() ->getResource().subUniqueKill())
			{
				//成功回调
				m_successCallback = [=](){
					Resource& resource = RunningData::getInstance()->getResource();
					resource.addUniqueKill(5);
					resource.save(); //保存

					resumeSchedulerAndActions();
				};
				//失败回调
				m_failCallback = [=](){
					resumeSchedulerAndActions();
				};

				pauseSchedulerAndActions();

				Shopping& shopping = RunningData::getInstance()->getShopping();
				shopping.setCatalog(k_supply);
				shopping.setIndex(k_unique_kill);
		
				ShoppingLayer* pShopping = ShoppingLayer::create();
				addChild(pShopping,1005);
				pShopping->setSuccessCallFun(m_successCallback);
				pShopping->setFailCallFun(m_failCallback);

				return;
			}
			CCLOG("bi sha") ;
			if (!iskillingall)
			{
				TString killallstring;
				killallstring += "*";
				int killnum = RunningData::getInstance() ->getResource().getUniqueKillNum();
				killallstring += killnum;
				killallNum -> setString(killallstring.data());
				showBisha();
			}
		}

		break;
	case ButtonTagHuDun:
		{
			if (!RunningData::getInstance() ->getResource().subShield())
			{
				//成功回调
				m_successCallback = [=](){
					Resource& resource = RunningData::getInstance()->getResource();
					resource.addShield(5);
					resource.save(); //保存

					resumeSchedulerAndActions();
				};
				//失败回调
				m_failCallback = [=](){

					resumeSchedulerAndActions();
				};
				pauseSchedulerAndActions();

				Shopping& shopping = RunningData::getInstance()->getShopping();
				shopping.setCatalog(k_supply);
				shopping.setIndex(k_shield);
		
				ShoppingLayer* pShopping = ShoppingLayer::create();
				addChild(pShopping,1005);
				pShopping->setSuccessCallFun(m_successCallback);
				pShopping->setFailCallFun(m_failCallback);

				return;
			}
			CCLOG("hu dun") ;
			if (!issheildexit)
			{
				TString sheildstring;
				sheildstring += "*";
				int sheildnum = RunningData::getInstance() ->getResource().getShieldNum();
				sheildstring += sheildnum;
				sheildNum -> setString(sheildstring.data());
				showSheild();
			}
		}

		break;

	case ButtonTagPause:
		{
			playSound("music/click.ogg");
			CCLOG("pause game!") ;
			CCDirector::sharedDirector()->pushScene(PauseLayer::scene());
		}

		break;

	default:
		break;
	}
}

void BattleManage::showBisha()
{
	Achievement& achieve = RunningData::getInstance() ->getAchievement();
	achieve.addUniqueKillTimes();
	achieve.save();

	iskillingall = true;
	bishaWords -> setVisible(true);
	sheildWords -> setVisible(false);
	unschedule(schedule_selector(BattleManage::setWordsInvisible));

	schedule(schedule_selector(BattleManage::reduceEnemyHpByTime),0.1);
	scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),1.5);
	showbishaEffect(0.0);
	scheduleOnce(schedule_selector(BattleManage::removeBisha),m_kill_time);


}

void BattleManage::setWordsInvisible(float dt)
{
	sheildWords -> setVisible(false);
	bishaWords -> setVisible(false);
	warningWord -> setVisible(false);
}

void BattleManage::showSheild()
{
	Achievement& achieve = RunningData::getInstance() ->getAchievement();
	achieve.addShieldTimes();
	achieve.save();

	// show sheild
	playSound("music/shield.ogg");
	showSheildEffect();
	sheildWords -> setVisible(true);
	bishaWords -> setVisible(false);
	unschedule(schedule_selector(BattleManage::setWordsInvisible));

	scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),1.5);
	if (!sheildExitForever)
	{
		scheduleOnce(schedule_selector(BattleManage::removeSheildEffect),m_sheild_time);
	}
	else
		sheildExitForever = false;
}

void BattleManage::showSheildEffect()
{
	issheildexit = true;
	sheild = CCSprite::createWithSpriteFrameName("bishaeffect1.png");
	sheild -> setPosition(ccp(400,0));
	sheild-> setAnchorPoint(ccp(0.5,0.0));
	CCArray *animaArray = CCArray::createWithCapacity(10);
	for (int j = 1; j <= 10; j++)
	{
		TString str;
		str += "sheild_protect";
		str += j;
		str += ".png";
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
		animaArray->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.1f);
	CCAnimate* animate = CCAnimate::create(animation);
	sheild -> runAction(CCRepeatForever::create(animate));
	addChild(sheild,10001);
}

void BattleManage::removeSheildEffect(float dt)
{
	issheildexit = false;
	sheild -> removeFromParent();
}

void BattleManage::reduceEnemyHpByTime(float dt)
{
	vector<Enemy*> enemyList = EnemyManage::oneself -> getEnemyList();
	for (unsigned int i = 0; i < enemyList.size(); ++i)
	{
		enemyList[i] -> reduceHp(m_kill_damage);
	}
}

void BattleManage::removeBisha(float dt)
{
	iskillingall = false;
	unschedule(schedule_selector(BattleManage::reduceEnemyHpByTime));
	unschedule(schedule_selector(BattleManage::showbishaEffect));

	if (m_gameover)
	{
		showWinLayer(true);
	}
}

void BattleManage::showbishaEffect(float dt)
{
	float posx = rand()%600 + 100;
	float posy = rand()%300 + 100;

	CCSprite* bisha = CCSprite::createWithSpriteFrameName("bishaeffect1.png");
	bisha -> setPosition(ccp(posx,posy));
	CCArray *animaArray = CCArray::createWithCapacity(10);
	for (int j = 1; j <= 10; j++)
	{
		TString str;
		str += "bishaeffect";
		str += j;
		str += ".png";
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
		animaArray->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.06f);
	CCAnimate* animate = CCAnimate::create(animation);
	bisha -> runAction(CCSequence::create(animate,CCCallFuncO::create(this,callfuncO_selector(BattleManage::oneBishaOver),bisha),NULL) );

	scheduleOnce(schedule_selector(BattleManage::shakeLayer),0.2);
	addChild(bisha,10001);
	//scheduleOnce(schedule_selector(BattleManage::showbishaEffect),0.5);
	schedule(schedule_selector(BattleManage::showbishaEffect),0.4); // 多次注册就不会顶替  提醒已注册?
}

void BattleManage::oneBishaOver(CCObject* pSender)
{
	CCSprite* sp = (CCSprite*)pSender;
	if (sp)
	{
		sp -> removeFromParent();
	}
}

CCRenderTexture* BattleManage::getScreenCapture(bool updateScreen)
{
	if (updateScreen)
	{
		CC_SAFE_RELEASE_NULL(s_pRenderTexture);
		s_pRenderTexture = CCRenderTexture::create(800, 480);
		s_pRenderTexture->retain();
		s_pRenderTexture->begin();
		CCDirector::sharedDirector()->getRunningScene()->visit();
		s_pRenderTexture->end();
	}
	return s_pRenderTexture;
}


void BattleManage::deleteGold(GoldAnimation *gold)
{
	removeChild(gold);
}

bool BattleManage::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	//点击屏幕
	
// #if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
// 	showWinLayer(true);
// #endif
	CCLOG("touchBegan!!") ;
	float x = pTouch->getLocation().x;
	float y = pTouch -> getLocation().y;
	if (y < 80)
	{
		return true;
	}
	//moveZhujiao(x/160 + 1);
	moveZhujiao(twopointdegree(ccp(380, 50),ccp(x,y)));
	firearms->ccTouchBegan(pTouch, pEvent);
	return true;
}

void BattleManage::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	//点击之后移动
	float x = pTouch->getLocation().x;
	float y = pTouch -> getLocation().y;
	if (y < 80)
	{
		return;
	}
	moveZhujiao(twopointdegree(ccp(380, 50),ccp(x,y)));
	firearms->ccTouchMoved(pTouch, pEvent);
}

void BattleManage::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	//松开屏幕
	float x = pTouch->getLocation().x;
	float y = pTouch -> getLocation().y;
	zhujiao -> stopAllActions();
	moveZhujiao(twopointdegree(ccp(380, 30),ccp(x,y)),true);
	firearms->ccTouchEnded(pTouch, pEvent);
}

void BattleManage::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{//如果当前为点击或移动状态，，正好来电话或者别的操作打断当前触摸事件时触发
	firearms->ccTouchCancelled(pTouch, pEvent);
}

void BattleManage::shakeLayer(float dt)
{
	playSound("music/uniqueskill.ogg");
	float movex = 15;
	float scalemax = 1.2;
	CCAction* ac = CCSequence::create(
		CCSpawn::create(CCMoveBy::create(0.032, ccp(movex,-movex)),
		CCSequence::create(CCScaleTo::create(0.032, scalemax),CCScaleTo::create(0.032, 1),NULL),
		NULL),
		CCSpawn::create(CCMoveBy::create(0.032, ccp(-movex,movex)),
		CCSequence::create(CCScaleTo::create(0.032, scalemax),CCScaleTo::create(0.032, 1),NULL),
		NULL),
		NULL);
	ac->setTag(111);
	this -> runAction(ac);
}

        
void BattleManage::addTipsWords(int waves)
{
	/*warningWord -> setVisible(true);
	scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),4.0);*/

	if (isrepeatGame)
	{
		return;
	}

	if (currentLevel == 1 && waves == 1)
	{
		// test新手引导
		scheduleOnce(schedule_selector(BattleManage::showTipsOne),3.1f);
	}
	else if (currentLevel == 1 && waves == 5)
	{
		scheduleOnce(schedule_selector(BattleManage::showTipsTwo),2.0f);
	}
	else if (currentLevel == 1 && waves == 7)
	{
		scheduleOnce(schedule_selector(BattleManage::showTipsThree),6.0f);
		m_gameover = true;
	}
	else if (currentLevel == 1 && waves == 11)
	{
		scheduleOnce(schedule_selector(BattleManage::showTipsFour),0.1f);
		scheduleOnce(schedule_selector(BattleManage::showTipsFive),5.0f);
	}
	else if (currentLevel == 3 && waves == 7)
	{
		warningWord -> setVisible(true);
		scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),4.0);

	}
	else if (currentLevel == 6 && waves == 6)
	{
		warningWord -> setVisible(true);
		scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),4.0);
	}
	else if (currentLevel == 9 && waves == 6)
	{
		warningWord -> setVisible(true);
		scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),4.0);
	}
	else if (currentLevel == 12 && waves == 2)
	{
		warningWord -> setVisible(true);
		scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),4.0);
	}
	else if (currentLevel == 12 && waves == 3)
	{
		warningWord -> setVisible(true);
		scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),4.0);
	}
	else if (currentLevel == 12 && waves == 4)
	{
		warningWord -> setVisible(true);
		scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),4.0);
	}
	else if (currentLevel == 12 && waves == 5)
	{
		warningWord -> setVisible(true);
		scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),4.0);
	}
	else if (currentLevel == 12 && waves == 6)
	{
		warningWord -> setVisible(true);
		scheduleOnce(schedule_selector(BattleManage::setWordsInvisible),4.0);
	}
}

void BattleManage::schedulePauseGame(float dt)
{
	pauseSchedulerAndActions();
}

void BattleManage::scheduleResumeGame(float dt)
{
	resumeSchedulerAndActions();
}

void BattleManage::showTipsOne(float dt)
{
	BattleData& bd = RunningData::getInstance()->getBattleData();
	TipsScene* tips = TipsScene::create(true,false);
	tips -> setTipString(bd.battlePrompt[0].title.c_str());
	addChild(tips,1003);
}
void BattleManage::showTipsTwo(float dt)
{
	BattleData& bd = RunningData::getInstance()->getBattleData();
	TipsScene* tips = TipsScene::create(true);
	tips -> setTipString(bd.battlePrompt[1].title.c_str());
	CCSprite* headicon = CCSprite::createWithSpriteFrameName("3_DownWalk_1.png");
	headicon -> setScale(2);
	headicon -> setPosition(ccp(400,240));
	tips -> addChild(headicon,10);
	addChild(tips,1003);
}
void BattleManage::showTipsThree(float dt)
{
	BattleData& bd = RunningData::getInstance()->getBattleData();
	TipsScene* tips = TipsScene::create(ccp(115,40));
	tips -> setTipString(bd.battlePrompt[2].title.c_str());
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(BattleManage::showBisha));
	tips -> setCallFun(func);
	addChild(tips,1003);
}
void BattleManage::showTipsFour(float dt)
{
	BattleData& bd = RunningData::getInstance()->getBattleData();
	TipsScene* tips = TipsScene::create(true);
	tips -> setTipString(bd.battlePrompt[3].title.c_str());
	CCSprite* headicon = CCSprite::createWithSpriteFrameName("9_DownWalk_1.png");
	headicon -> setScale(1.5);
	headicon -> setPosition(ccp(400,240));
	tips -> addChild(headicon);
	addChild(tips,1003);
}
void BattleManage::showTipsFive(float dt)
{
	BattleData& bd = RunningData::getInstance()->getBattleData();
	TipsScene* tips = TipsScene::create(ccp(680,40));
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(BattleManage::showSheild));
	sheildExitForever = true;
	tips -> setCallFun(func);
	tips -> setTipString(bd.battlePrompt[4].title.c_str());
	addChild(tips,1003);
}
void BattleManage::showTipsSix(float dt)
{
	BattleData& bd = RunningData::getInstance()->getBattleData();
	TipsScene* tips = TipsScene::create(ccp(400,240),true);
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(BattleManage::gotoBuyLayer));
	tips -> setCallFun(func);
	tips -> setTipString(bd.battlePrompt[5].title.c_str());
	addChild(tips,1003);
}

void BattleManage::showTipsInstensigy(float dt)
{
	BattleData& bd = RunningData::getInstance()->getBattleData();

	MultiTipsScene* tips = MultiTipsScene::create();
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(BattleManage::showTipPoint));
	tips -> setCallFun(func);
	tips -> setTipString(bd.battlePrompt[7].title.c_str());
	addChild(tips,1003);

	pauseSchedulerAndActions();
}

void BattleManage::showTipPoint()
{
	MultiTipsScene* tips = MultiTipsScene::create(ccp(488,155),false,0);
	CCCallFunc* func = CCCallFunc::create(this,callfunc_selector(BattleManage::gotoIntensifyPage));
	tips -> setCallFun(func);
	addChild(tips,1004);
}


void BattleManage::gotoIntensifyPage()
{
	RunningData::getInstance()->isStrengthLevelupPageTip = true;
	CCDirector::sharedDirector()->pushScene(StrengthLevelup::scene());
}

void BattleManage::gotoBuyLayer()
{
	// 激活成功之后调用  showWinLayer();

	int stage = RunningData::getInstance()->getGameLevel().getStage();
	if(stage == 1)
	{
			//成功回调
		m_successCallback = [=](){
			CCLOG("GOTO winlayer!!");

			//showWinLayer();
			isBuyedShowSuccess = true;
			resumeSchedulerAndActions();

			Resource& res = RunningData::getInstance()->getResource();
			res.setShieldNum(res.getShieldNum() + 1);
			res.setUniqueKillNum(res.getUniqueKillNum() + 1);
			res.addGold(5000);
			res.save();
		};
		//
		m_failCallback = [=](){
			isBuyedShowFail = true;
			resumeSchedulerAndActions();
			//RunningData::getInstance()->isMainTip = true;
			//CCDirector::sharedDirector()->popToRootScene();
		};

		pauseSchedulerAndActions();

		Shopping& shopping = RunningData::getInstance()->getShopping();
		shopping.setCatalog(k_supply);
		shopping.setIndex(k_give_gift);
	
		ShoppingLayer* pShopping = ShoppingLayer::create();
		addChild(pShopping,1005);
		pShopping->setSuccessCallFun(m_successCallback);
		pShopping->setFailCallFun(m_failCallback);

		//保存关卡数据
		GameLevel& gl = RunningData::getInstance()->getGameLevel();
		gl.setIsWinOne(1);
		gl.saveLevelInfo();

		RunningData::getInstance()->isMainTip = true;
	} else 
	{
		showWinLayer();
	}

}

void BattleManage::removeTips(CCObject* pSender)
{
	CCNode* node = (CCNode*)pSender;
	if (node)
	{
		node -> removeFromParent();
	}
}

BattleManage::~BattleManage()
{
	CCAnimationCache::sharedAnimationCache()->purgeSharedAnimationCache();
}
