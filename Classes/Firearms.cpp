#include "Firearms.h"
#include "Bullet.h"
#include "math.h"
#include "tool.h"
#include "ZombieSound.h"
#include "data_center/RunningData.h"

bool Firearms::init()
{
	RateOfFireTime = 0;
	RateOfFire = 0.1f;
	clickSwitch = false;
	touchbegin = false;
	initialPoint = ccp(400, 50);
	basePoint = ccp(400,50);
	bullettype = AK47;
	hasCollsionRect = false;
	shootBulletNum = 0;
	//initStageData();
	return true;
}

void Firearms::setBulletType(BulletType type,int hero)
{
	bullettype = type;
	currentHero = hero;
	switch(bullettype)
	{
	case VulcanM61:
		{
			RateOfFire = 0.4f;
		}
		break;
	case MG4:
		{
			gunheight = 30;
			RateOfFire = 0.4f;
		}
		break;
	case RPG_7:
		{
			initialPoint = ccp(400, 50);
			basePoint = ccp(400,50);
			RateOfFire = 0.3f;
			gunheight = 57 + 20;  // 像素  枪的长度加上旋转的力臂
		}
		break;
	case M107:
		{
			RateOfFire = 0.4;
			gunheight = 70;
		}
		break;
	case M1014:
		{
			RateOfFire = 0.4;
			gunheight = 360;
		}
		break;
	default:
		RateOfFire = 0.1;
		break;
	}
	// 修改子弹速率
	RateOfFire = RateOfFire * (1 -  RunningData::getInstance() ->getReinfoce().m_reinfoceSys[2].value / 10.0);
}

void Firearms::updata(float dt)
{
	if (RateOfFireTime < RateOfFire)
	{
		if (bullettype == M107 && getChildByTag(9999) != 0)
		{
			RateOfFireTime = 0.3f;
		}
		else
			RateOfFireTime += dt;
	}

	for (unsigned int i = 0; i < bulletList.size(); ++i)
	{
		if (bulletList[i] != NULL)
		{
			if (hasCollsionRect)
			{
				if (collsionRect.containsPoint(bulletList[i] -> getPosition()) || collsionRect2.containsPoint(bulletList[i] -> getPosition()))
				{
					bulletList[i] -> actionAfterCollsion();
				}
			}

			if (bulletList[i]->life)
			{
				bulletList[i]->updata(dt);
			}
			else
			{
				bulletList[i] -> removeFromParent();
				vector<Bullet*>::iterator it = bulletList.begin() + i;
				bulletList.erase(it);
			}
		}
	}
	if (clickSwitch)
	{
		buildBullet(clickPosition.x, clickPosition.y,bullettype);
	}
}

void Firearms::createCollisionRect(int type)
{
	hasCollsionRect = true;
	if (type == 1)  // 第二关地图
	{
		collsionRect = CCRectMake(540,170,130,90);
		collsionRect2 = CCRectMake(0,0,0,0);
	}
	else                // 第三关地图
	{
		collsionRect = CCRectMake(115,115,60,90);
		collsionRect2 = CCRectMake(530,250,270,230);
	}
}

void Firearms::buildBullet(float x, float y,BulletType type)
{
	if ((RateOfFireTime < RateOfFire) || !touchbegin) 
	{
		return;
	}
	touchx = x;
	touchy = y;
	RateOfFireTime = 0;
	if (bullettype == RPG_7)
	{
		playSound("music/gatlingfire.ogg");
		BattleManage::oneself -> fireGunAnimation();
		createBullet();
		scheduleOnce(schedule_selector(Firearms::createBulletAtPos),0.05f);
		scheduleOnce(schedule_selector(Firearms::createBulletAtPos2),0.10f);
	}
	else if (bullettype == M107)
	{
		if (getChildByTag(9999) != NULL)
		{
			return;
		}
		playSound("music/flamethrowerfire.ogg");
		createTouchExitBullet();
		schedule(schedule_selector(Firearms::changeGunType),4.0f);
	}
	else if (bullettype == M1014)
	{
		shootBulletNum ++;
		playSound("music/lasergunfire.ogg");
		createBullet();

		if (shootBulletNum >= 4)
		{
			shootBulletNum = 0;
			setBulletType(MG4,3);
		}
	}
	else if (bullettype == MG4)
	{
		playSound("music/flamethrowerfire.ogg");
		createBullet();
		setBulletType(M1014,3);
		//bullettype = M1014;
	}
	else
	{
		playSound("music/flamethrowerfire.ogg");
		createBullet();			
	}
}

void Firearms::changeGunType(float dt)
{
	if (currentHero == 1)
	{
		bullettype = VulcanM61;
		if (getChildByTag(9999) != NULL)
		{
			//specialBullet -> setVisible(false);
		}
		createBullet();
		bullettype = M107;
		scheduleOnce(schedule_selector(Firearms::changeGunTypeBack),0.5);
	}
}

void Firearms::changeGunTypeBack(float dt)
{
	if (currentHero == 1)
	{
		if (getChildByTag(9999) != NULL)
		{
			specialBullet -> setVisible(true);
		}
	}
}

void Firearms::createBullet()
{
	Bullet* bu = Bullet::create(bullettype, twoPoint(initialPoint, ccp(touchx, touchy)));
	bu->setPosition(initialPoint);
	bulletList.push_back(bu);
	this->addChild(bu, 0);
}

void Firearms::createTouchExitBullet()
{
	specialBullet = Bullet::create(bullettype, twoPoint(initialPoint, ccp(touchx, touchy)));
	specialBullet->setPosition(initialPoint);
	bulletList.push_back(specialBullet);
	this->addChild(specialBullet, 0,9999);
}

void Firearms::createBulletAtPos2(float dt)
{
	playSound("music/gatlingfire.ogg");
	CCPoint createPoint = initialPoint + ccp(-3,-3);
	float tx = touchx - 3;
	float ty = touchy - 3;
	Bullet* bu = Bullet::create(bullettype, twoPoint(createPoint, ccp(tx, ty)));
	bu->setPosition(createPoint);
	bulletList.push_back(bu);
	this->addChild(bu, 0);
}

void Firearms::createBulletAtPos(float dt)
{
	playSound("music/gatlingfire.ogg");
	CCPoint createPoint = initialPoint + ccp(3,3);
	float tx = touchx + 3;
	float ty = touchy + 3;
	Bullet* bu = Bullet::create(bullettype, twoPoint(createPoint, ccp(tx, ty)));
 	bu->setPosition(createPoint);
	bulletList.push_back(bu);
	this->addChild(bu, 0);
}

bool Firearms::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	touchbegin1 = true;
	touchbegin = true;
	float x = pTouch->getLocation().x;
	float y = pTouch->getLocation().y;
	clickPosition.x = touchx = x;
	clickPosition.y = touchy = y;

	resetInitialPoint();
	buildBullet(x, y,bullettype);
	clickSwitch = true;
	touchbegin1 = false;
	return true;
}

void Firearms::resetInitialPoint()
{
	// 根据枪长度调整子弹生成位置
	float degree = twopointdegree(basePoint,ccp(touchx,touchy)) / 180.0 * PI;
	float addx = 0.0;
	float addy = 0.0;
	if (degree > 90)
	{
		degree -= 90;
		addx = sin(degree) * gunheight;
		addy = cos(degree) * gunheight;
	}
	else
	{
		addy = sin(degree) * gunheight;
		addx = cos(degree) * gunheight;
		addx = -addx;
	}
	initialPoint = ccpAdd(basePoint,ccp(addx,addy));
}

void Firearms::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	float x = pTouch->getLocation().x;
	float y = pTouch->getLocation().y;
	clickPosition.x = touchx = x;
	clickPosition.y = touchy = y;

	resetInitialPoint();

	if (bullettype == M107)
	{
		if (y < initialPoint.y)
		{
			ccTouchEnded(pTouch,pEvent);
			return; // 直接return会导致枪在动  喷火听了
		}
		if (getChildByTag(9999) != NULL)
		{
			RateOfFireTime = 0.0f;   // 跟这个时间有关系。。。。
			specialBullet -> touchmove(initialPoint,twoPoint(specialBullet -> getPosition(), ccp(touchx, touchy)));
		}
	}
	else
		buildBullet(x, y,bullettype);
}

void Firearms::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (bullettype == M107)
	{
		if (getChildByTag(9999) != NULL)
		{
			specialBullet -> touchend();
		}
		unschedule(schedule_selector(Firearms::changeGunType));
	}
	clickSwitch = false;
	touchbegin = false;
}

void Firearms::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}