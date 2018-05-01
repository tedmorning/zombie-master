#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;

#define MAP_BG_zOrder 0  //��ͼ���������
#define MAP_COVER_zOrder 20 //��ͼ�ڵ������
#define Bullet_zOrder 31 //�ӵ������

#define Gold_zOrder 40 // ��Ҷ������

#define HP_Zorder 2 //Ѫ�����

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

	//Ӣ��  �ؿ����  �Ƿ�Ϊ����ģʽ
	static cocos2d::CCScene* scene(int hero,int level,bool isrepeat);

	static BattleManage* createWithInfo(int hero,int level,bool isrepeat);

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	void updata(float dt);

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	//����ͼƬ����
	void loadImage();
	//�Ѷ������浽�ڴ���
	void loadAnimation();

	/* ����һ����Ҷ���
	 * number �������
	 * point  ��Ҷ���λ��
	 */
	void buildGold(short number, CCPoint point);
	int getTotalGold;
	int killedTotalZombie;

	//ɾ����Ҷ���
	void deleteGold(GoldAnimation *gold);

	//ָ��BattleManage�Լ�
	static BattleManage *oneself;

	CCRenderTexture* getScreenCapture(bool updateScreen);

	void changeHeroBlood(int changeValue);

	//ǹе��
	Firearms *firearms;

	int currentLevel;
	int currentHero;
private:
	//UI����
	TouchGroup* ui;

	//��ͼ����(���Ƶ�ͼͼƬ)
	Map* map;

	//���������
	EnemyManage *enemyManage;

	//����ͼƬ
	CCSprite* zhujiao;
	CCSprite* zhujiaoleg;
	CCSprite* zhujiaogun;
	CCSprite* heroicon;
	int zhujiaoactionindex;

	//��ʬ����
	EnemyData *data;

	//װ������
	WeaponData* weaponsData;

	//Ѫ��
	int m_hero_blood;
	//��Ѫ��
	float m_hero_total_blood;
	//����ֵ
	int m_sheild_num;
	float m_sheild_time;
	float m_kill_time;
	float m_kill_damage;
	//Ѫ����
	UILoadingBar* bloodbar;
	//������
	UILoadingBar* progressbar;
	CCSprite* progressIcon;
	//�Ʒѳɹ���ص�
	std::function<void()> m_successCallback;
	//�Ʒ�ʧ�ܺ�ص�
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
	void changeHero(int direct);   // ������ɫ
	CCSprite* heroiconLeft;
	CCSprite* heroiconRight;
	int leftHeroID;
	int rightHeroID;
	int heroTemp;
	
	bool isrepeatGame;  // �Ƿ�Ϊ����ģʽ

	void shakeLayer(float dt);

	// �������� ����  �͵�ͼ  �����͵�ͼ��
	void createSceneAndMap();

public:
	// ������ǹ�Ķ���
	void fireGunAnimation();


	// չʾ��ʾ����
	void addTipsWords(int waves);
	void removeTips(CCObject* pSender);

private:
	// ��ʱչʾ����������
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
