#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;

#define MAP_BG_zOrder 0  //地图背景层深度
#define MAP_COVER_zOrder 20 //地图遮挡层深度
#define Bullet_zOrder 31 //子弹的深度

#define Gold_zOrder 40 // 金币动画深度

#define HP_Zorder 2 //血条深度

class Map;
class Enemy;
class EnemyManage;
class Firearms;
class EnemyData;
class GoldAnimation;
class WeaponData;

class BattleManage :
	public cocos2d::CCLayer
{
public:
	~BattleManage();

	virtual bool init();

	virtual void onEnter();

	virtual void onExit() ;

	//英雄  关卡编号  是否为无限模式
	static cocos2d::CCScene* scene(int hero,int level,bool isrepeat);

	static BattleManage* createWithInfo(int hero,int level,bool isrepeat);

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	void updata(float dt);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	//加载图片对像
	void loadImage();
	//把动画缓存到内存中
	void loadAnimation();

	/* 创建一个金币动画
	 * number 金币数量
	 * point  金币动画位置
	 */
	void buildGold(short number, CCPoint point);
	int getTotalGold;
	int killedTotalZombie;

	//删除金币动画
	void deleteGold(GoldAnimation *gold);

	//指向BattleManage自己
	static BattleManage *oneself;

	CCRenderTexture* getScreenCapture(bool updateScreen);

	void changeHeroBlood(int changeValue);

	//枪械类
	Firearms *firearms;

	int currentLevel;
	int currentHero;
private:
	//UI界面
	TouchGroup* ui;

	//地图对像(绘制地图图片)
	Map* map;

	//管理敌人类
	EnemyManage *enemyManage;

	//主角图片
	CCSprite* zhujiao;
	CCSprite* zhujiaoleg;
	CCSprite* zhujiaogun;
	CCSprite* heroicon;
	int zhujiaoactionindex;

	//僵尸数据
	EnemyData *data;

	//装备数据
	WeaponData* weaponsData;

	//血量
	int m_hero_blood;
	//总血量
	float m_hero_total_blood;
	//护盾值
	int m_sheild_num;
	float m_sheild_time;
	float m_kill_time;
	float m_kill_damage;
	//血量条
	UILoadingBar* bloodbar;
	//进度条
	UILoadingBar* progressbar;
	CCSprite* progressIcon;
	//计费成功后回调
	std::function<void()> m_successCallback;
	//计费失败后回调
	std::function<void()> m_failCallback;
public:
	void checkshowchengjiu();
	bool isShowingChengjiu;
	CCSprite* showChengjiuBG;
	CCSprite* showChengjiuTop;
	void scheduleCouldShowSuccess(float dt);

	CCLabelTTF* killallNum;
	CCLabelTTF* sheildNum;
	void setProgressBar(int percent);
	void moveZhujiao(float degree,bool repeat = false);
	CCLayer* bishaWords;
	void showBisha();
	void showbishaEffect(float dt);
	void removeBisha(float dt);

	void gotoIntensifyPage();
	void reduceEnemyHpByTime(float dt);
	CCLayer* sheildWords;
	void showSheild();
	void showSheildEffect();
	void removeSheildEffect(float dt);
	bool issheildexit;
	bool iskillingall;
	bool iskillingallOver;
	void oneBishaOver(CCObject* pSender);
	CCSprite* sheild;

	void setWordsInvisible(float dt);

	CCSprite* warningWord;
private:
	static CCRenderTexture* s_pRenderTexture;
	void changeHero(int direct);   // 更换角色
	CCSprite* heroiconLeft;
	CCSprite* heroiconRight;
	int leftHeroID;
	int rightHeroID;
	int heroTemp;
	
	bool isrepeatGame;  // 是否为无限模式

	void shakeLayer(float dt);

	// 创建背景 场景  和地图  场景和地图绑定
	void createSceneAndMap();

public:
	// 创建开枪的动画
	void fireGunAnimation();


	// 展示提示动画
	void addTipsWords(int waves);
	void removeTips(CCObject* pSender);

private:
	// 延时展示的新手引导
	void showTipsOne(float dt);
	void showTipsTwo(float dt);
	void showTipsThree(float dt);
	void showTipsFour(float dt);
	void showTipsFive(float dt);
	void showTipsSix(float dt);
	void showTipsInstensigy(float dt);
	void schedulePauseGame(float dt);
	void scheduleResumeGame(float dt);
	void showTipPoint();
	bool showBuyLayer;
	bool isBuyedShowSuccess;
	bool isBuyedShowFail;
	bool isGoFailPage;
	bool sheildExitForever;
	void gotoBuyLayer();
	void showSuccessDelay(float dt);
	bool isshowingSuccessDelay;
	CCLabelTTF* overGameTips;	void showWinLayer(bool issuccess = false);

	bool m_gameover;
};
