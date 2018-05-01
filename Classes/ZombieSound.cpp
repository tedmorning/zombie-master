#include "ZombieSound.h"
void setSoundOn(bool flag)
{
	bool isSoundOn = flag;
    if (isSoundOn) {
        SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    }
    else
    {
        SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
    }
}
void preloadSounds()
{

	return;
SimpleAudioEngine::sharedEngine()->preloadEffect("music/game0.mp3");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/game1.mp3");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/game2.mp3");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/game3.mp3");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/win.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/lose.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/click.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/purchase.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/strengthen.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/operationfail.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/gatlingfire.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/flamethrowerfire.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/lasergunfire.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/bazookafire.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/uniqueskill.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/shield.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/treat.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/summon.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/zombiehit.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/zombiedead.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/bossdead.ogg");
SimpleAudioEngine::sharedEngine()->preloadEffect("music/bossdeformation.ogg");

}
void playSound(const char* soundname)
{
    SimpleAudioEngine::sharedEngine()->playEffect(soundname);
}

void playButtonSound()
{
    playSound("music/click.ogg");
}

void setSoundVolume(float volume)
{
	SimpleAudioEngine::sharedEngine() ->setBackgroundMusicVolume(volume);
	SimpleAudioEngine::sharedEngine()->setEffectsVolume(volume);
}

void playBackgroundMusic(const char* bg,bool repeat)
{
	SimpleAudioEngine::sharedEngine() -> playBackgroundMusic(bg,repeat);
}

void playUIBackgroundMusic()
{
	playBackgroundMusic("music/game0.mp3", true);
}