#include "AppDelegate.h"
#include "GameMainMenu.h"
#include "BattleManage.h"
#include "StrengthLevelup.h"
#include "SimpleAudioEngine.h"
#include "LoadingScene.h"
#include "data_center/Resource.h"
#include "data_center/RunningData.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#endif
using namespace CocosDenshion;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "MobClickCpp.h"
#endif

USING_NS_CC;

bool AppDelegate::pauseSwitch = true;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    pEGLView->setDesignResolutionSize(800, 480, kResolutionExactFit);
    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	//CCScene *pScene = GameMainMenu::scene();
    //CCScene *pScene = GameMainMenu::scene();  

	CCFileUtils::sharedFileUtils()->addSearchPath("data");
	CCScene *pScene = LoadingLayer::scene();

    // run
    pDirector->runWithScene(pScene);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("541b996ffd98c5ae2706181e", "CJYXDZJS_91_sk_001");
	MOBCLICKCPP_START_WITH_APPKEY("5508ef95fd98c5404e000f0f");
	
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// 	JniMethodInfo jni;
// 	if (JniHelper::getStaticMethodInfo(jni, "com/honglongguo/zombie/Zombie", "getGold", "()I")) {
// 		int temp = jni.env->CallStaticIntMethod(jni.classID, jni.methodID);
// 		Resource& resource = RunningData::getInstance()->getResource();
// 		resource.addGold(temp);
// 		resource.save();
// 	}
#endif

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::applicationDidEnterBackground();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
	pauseSwitch = true;

// #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
// 	JniMethodInfo jni;
// 	if (JniHelper::getStaticMethodInfo(jni, "com/honglongguo/zombie/Zombie", "getGold", "()I")) {
// 		int temp = jni.env->CallStaticIntMethod(jni.classID, jni.methodID);
// 		Resource& resource = RunningData::getInstance()->getResource();
// 		resource.addGold(temp);
// 		resource.save();
// 	}
// #endif
    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::applicationWillEnterForeground();
#endif
}
