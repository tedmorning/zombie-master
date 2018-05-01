#include "JniCommon.h"

#include "cocos-ext.h"  

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  

#include <jni.h>  

#include "platform/android/jni/JniHelper.h"  
#include "MobClickCpp.h"
#endif
CCObject * m_payObj = NULL;
Sel_Pay_Event m_payEvent = NULL;
int m_payType=0;
extern "C"
{
void exitGame()
{

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台

//     JniMethodInfo methodInfo;
// 
//     bool isHave = JniHelper::getStaticMethodInfo(methodInfo,
// 		
//             "com/honglongguo/zombie/THandler",//需要调用的Java文件
// 
//             "exit",//调用的方法名
// 
//             "()V");//参数
// 
//     if(isHave){
// 		   CCLOG("the keyDown method is execute");
//            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
// 
//     }else{
//             CCLog("the keyDown method is not exits");
//     }
	JniMethodInfo jni;

	if (JniHelper::getStaticMethodInfo(jni, "com/ltgame/jiangshi/Zombie", "exit", "()V")) {
		jni.env->CallStaticVoidMethod(jni.classID , jni.methodID);
	}


    #endif
}
}

bool isPay=true;

PAY_CALLBACK callback;

void payCode(int payType,CCObject * obj, Sel_Pay_Event payEvent)
{

	m_payObj = obj;
	m_payEvent = payEvent;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
	JniMethodInfo jni;
	
	if (JniHelper::getStaticMethodInfo(jni, "com/ltgame/jiangshi/Zombie", "pay", "(I)V")) {
		jni.env->CallStaticVoidMethod(jni.classID , jni.methodID , payType);
	}

	//添加友盟事件
	m_payType=payType;
	switch (payType)
	{

	case k_pay_logingif:
		umeng::MobClickCpp::event("js_buy02_click");
		break;
	case k_pay_gold10000:
		umeng::MobClickCpp::event("js_buy02_click");
		break;
	case k_pay_revieve:
		umeng::MobClickCpp::event("js_buy03_click");
		break;
	case k_pay_fulllevel:
		umeng::MobClickCpp::event("js_buy04_click");
		break;
	case k_pay_bisha:
		umeng::MobClickCpp::event("js_buy05_click");
		break;
	case k_pay_hudun:
		umeng::MobClickCpp::event("js_buy06_click");
		break;
	case k_pay_newgift:
		umeng::MobClickCpp::event("js_buy07_click");
		break;
	case k_pay_supergift:
		umeng::MobClickCpp::event("js_buy08_click");
		break;
	case k_pay_revievegift:
		umeng::MobClickCpp::event("js_buy09_click");
		break;
	case k_pay_award:
		umeng::MobClickCpp::event("js_buy10_click");
		break;

	default:
		break;
	}
	


#endif




#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	if (m_payEvent&&m_payObj)
	{
		(m_payObj->*m_payEvent)(true);
	}
#endif

}



void savePaycode(const char* paycode){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
	JniMethodInfo jni;
	if (JniHelper::getStaticMethodInfo(jni, "com/honglongguo/zombie/Zombie", "savePaycode", "(Ljava/lang/String;)V")) {
		jclass str_cls = jni.env->FindClass("java/lang/String");
		jstring str1 = jni.env->NewStringUTF(paycode);
		jni.env->CallStaticVoidMethod(jni.classID , jni.methodID , str1);
	}
#endif
}

void payForProduct(PAY_CALLBACK callbackparam) {
	callback=callbackparam;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	callback(true);
#endif

	if(!isPay)
	{
		callback(true);
	}
	else
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
		JniMethodInfo minfo;
		bool isHave = false;
		isHave = JniHelper::getStaticMethodInfo(minfo,"com/honglongguo/zombie/Zombie","getJavaActivity","()Ljava/lang/Object;");
		jobject activityObj;
		if (isHave)
		{
			//调用静态函数getJavaActivity，获取java类对象。
			activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
		}
		isHave = JniHelper::getMethodInfo(minfo,"com/honglongguo/zombie/Zombie","payForProduct", "()V");
		if (isHave)
		{
			minfo.env->CallVoidMethod(activityObj, minfo.methodID);
		}
		CCLog("11111111111111");
#endif
	}
}


extern "C" {

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  

	void Java_com_ltgame_jiangshi_Zombie_payCallBackSuccess(JNIEnv* env,jobject object)
	{
		//callback(true);	
		CCLOG("end pay success callback");
		//添加友盟事件
		if (m_payEvent&&m_payObj)
		{
			(m_payObj->*m_payEvent)(true);
		}
		switch (m_payType)
		{
		case k_pay_logingif:
			umeng::MobClickCpp::event("js_buy01_success");
			break;
		case k_pay_gold10000:
			umeng::MobClickCpp::event("js_buy02_success");
			break;
		case k_pay_revieve:
			umeng::MobClickCpp::event("js_buy03_success");
			break;
		case k_pay_fulllevel:
			umeng::MobClickCpp::event("js_buy04_success");
			break;
		case k_pay_bisha:
			umeng::MobClickCpp::event("js_buy05_success");
			break;
		case k_pay_hudun:
			umeng::MobClickCpp::event("js_buy06_success");
			break;
		case k_pay_newgift:
			umeng::MobClickCpp::event("js_buy07_success");
			break;
		case k_pay_supergift:
			umeng::MobClickCpp::event("js_buy08_success");
			break;
		case k_pay_revievegift:
			umeng::MobClickCpp::event("js_buy09_success");
			break;
		case k_pay_award:
			umeng::MobClickCpp::event("js_buy10_success");
			break;

		default:
			break;
		}


		
	}


	void Java_com_ltgame_jiangshi_Zombie_payCallBackFailed(JNIEnv* env,jobject object)
	{
		//callback(false);
		CCLOG("pay failed callback");

		if (m_payEvent&&m_payObj)
		{
			(m_payObj->*m_payEvent)(false);
		}
	}
#endif
}

const char * _text(const char * key)
{
	CCDictionary *m_strings = CCDictionary::createWithContentsOfFile("string.xml");
	const char *value = ((CCString*)m_strings->objectForKey(key))->m_sString.c_str();
	return value;
}
