#include "LoadingScene.h"
#include "tool.h"
#include "ZombieSound.h"
#include "data_center\RunningData.h"
#include "GameMainMenu.h"


CCScene* LoadingLayer::scene()
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	LoadingLayer *layer = LoadingLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LoadingLayer::init()
{
	if (!CCLayer::init())
		return false;
	
	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//当前层的位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCLayerColor* layercolor = CCLayerColor::create(ccc4(255,255,255,255),800,480) ;
	addChild(layercolor) ;
// 
// 	ui = TouchGroup::create();
// 
// 	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/loadingLayer.ExportJson"));
// 	//ui->setVisible(false);
// 	addChild(ui, 2);

	//hideDot();

	num = 0;


	CCSprite * logo = CCSprite::create("logo.png");
	logo->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	this->addChild(logo,1000);
	//schedule(schedule_selector(LoadingLayer::showDot),0.1);
	logo->setScale(2.5);
	scheduleOnce(schedule_selector(LoadingLayer::loading),0.1);


	return true;
}

void LoadingLayer::loading(float dt)
{
	//读本地数据
	Config& config = RunningData::getInstance()->getConfig();

	float volume = config.getSoundVolume();

	::setSoundVolume(volume);

	::preloadSounds();

	//unschedule(schedule_selector(LoadingLayer::showDot));

	CCScene *pScene = GameMainMenu::scene(true);
	CCDirector::sharedDirector()->replaceScene(pScene);

}
void LoadingLayer::showDot(float dt)
{
	num++;
	if(num>3)
	{
		hideDot();
		num = 1;
	}
	
	char tem[10];

	sprintf(tem, "dot_%i", num);

	UIImageView* pImageView = imageObj_name(ui, tem);
	pImageView->setVisible(true);

}

void LoadingLayer::hideDot()
{
	UIImageView* pImageViewOne = imageObj_name(ui, "dot_1");
	UIImageView* pImageViewTwo = imageObj_name(ui, "dot_2");
	UIImageView* pImageViewThree = imageObj_name(ui, "dot_3");

	pImageViewOne->setVisible(false);
	pImageViewTwo->setVisible(false);
	pImageViewThree->setVisible(false);
}
