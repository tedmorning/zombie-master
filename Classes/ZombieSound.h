#include "cocos-ext.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

void preloadSounds();
void setSoundOn(bool flag);
void playSound(const char* soundname);
void playButtonSound();
void setSoundVolume(float volume);
void playBackgroundMusic(const char* bg,bool repeat);
void playUIBackgroundMusic();