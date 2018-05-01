#include "cocos-ext.h"  
#include "cocos2d.h"
using namespace cocos2d;
using namespace cocos2d::extension;
#ifndef _JNICOMMON_H_
#define _JNICOMMON_H_
enum PayType
{
	k_pay_logingif,
	k_pay_gold10000,

	k_pay_revieve,
	k_pay_fulllevel,
	k_pay_bisha,
	k_pay_hudun,
	k_pay_newgift,
	k_pay_supergift,
	k_pay_revievegift,
	k_pay_award,
	k_pay_story,

	k_pay_exit,
	k_pay_logingif_free
	
};

typedef void (*PAY_CALLBACK)(bool);
typedef void (CCObject::*Sel_Pay_Event)(bool result);
extern "C"
{
void exitGame();
}
const char * _text(const char * key);
extern void savePaycode(const char* paycode);
extern void payForProduct(PAY_CALLBACK callbackparam);


void payCode(int payType, CCObject * obj, Sel_Pay_Event payEvent);

#endif