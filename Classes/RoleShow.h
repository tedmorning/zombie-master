#ifndef __ROLE_SHOW_H__
#define __ROLE_SHOW_H__
#include "tool.h"
#include "Bullet.h"

enum battle_role
{
	k_battle_blackwidow = 1,
	k_battle_wolverine,
	k_battle_ironmen
};

class RoleShow : public CCNode
{
public:
	bool init();
	CREATE_FUNC(RoleShow);

	void resetArea(const CCPoint& location, const CCSize& size);
	void showHeroAnimation(int currentHero, const CCPoint& offsetPoint);
	void createBullet(int type, const CCPoint& startPoint, const CCPoint& endPoint);

	void process(float dt);
	void pause();
	void resume();
	void changeHero(int currentHero,const CCPoint& offsetPoint);

	const CCPoint& getLocataion();
	const CCSize& getSize();

private:

	void moveHero();
	void visit();	
	void loadAnimation();
	void addBullet(float dt);
	void roleChangeAngle(float dt);
	void createBulletAtPos(float dt);
	void createBulletAtPos2(float dt);

	void firegunEffect();
	void showBoom(const CCPoint& point);
	void removeSelf(CCNode* pSender);
	void wolverineGunAnimation();
	void createLaserBullet(const CCPoint& startPoint);

	CCPoint m_location;
	CCSize m_size;
	CCRect rect;

	int heroAngle;
	bool heroAngleOrien;

	int wolfBullectIndex;
	CCPoint endPointWolf[7];
	bool epIndexOrien;

    //保存子弹
	vector<Bullet*> bulletList;
	BulletType m_bulletType;
	CCSprite* pFiregun;
	CCSprite* jiguangGun;

	//子弹开始，结束点
	CCPoint startPoint;
	CCPoint endPoint;

	CCSprite* zhujiao;
	CCSprite* zhujiaoleg;
	CCSprite* zhujiaogun;

	float bulletSpeed;
	int m_currentHero;
	int m_blackBullet;
	int m_ironmanBullet;
	int m_ironmanBulletTwo;
	CCPoint m_offsetPoint;

};

#endif
