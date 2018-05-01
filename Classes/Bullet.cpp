#include "Bullet.h"
#include "math.h"
#include "tool.h"
#include "EnemyManage.h"
#include "BattleManage.h"
#include "data_center/RunningData.h"

Bullet* Bullet::create(BulletType type, float angle)
{
	Bullet* bu = new Bullet();
	if (bu->init(type, angle))
	{
		bu->autorelease();
		return bu;
	}
	CC_SAFE_DELETE(bu);
	return NULL;
}

bool Bullet::init(BulletType type, float ang)
{
	life = true;
	isbooming = false;
	iscreateForZombie = true;
	istouchmoved = false;
	killnum = 0;
	boomtime = 0.6; // 爆炸的时间！！
	bulletType = type;

	float shootangle = ang/PI*180;
	if (shootangle >= 90 && shootangle <= 180)
	{
		shootangle += 180;
		ang += PI;
	}
	else if (shootangle >= 180 && shootangle <= 270)
	{
		shootangle -= 180;
		ang -= PI;
	}

	this->angle = ang;
	this->type = type;

	if (type == VulcanM61)
	{
		attack = 60;
		attack += RunningData::getInstance() ->getReinfoce().m_reinfoceSys[1].value;
		img = CCSprite::createWithSpriteFrameName("rocketgunbullet1.png");
	}
	else if (type == M107)
	{
		attack = 8;
		attack += RunningData::getInstance() ->getReinfoce().m_reinfoceSys[1].value * 0.1;
		img = CCSprite::createWithSpriteFrameName("fireguneffect1.png");
		img -> setAnchorPoint(ccp(0.5,0.0));
	}
	else if (type == RPG_7)
	{
		attack = 15;
		attack += RunningData::getInstance() ->getReinfoce().m_reinfoceSys[1].value;
		img = CCSprite::createWithSpriteFrameName("firegodgunbullet.png");
	}
	else if (type == M1014)
	{
		attack = 20;
		attack += RunningData::getInstance() ->getReinfoce().m_reinfoceSys[1].value;
		img = CCSprite::createWithSpriteFrameName("jiguangEffect1.png");
		runbulletAction();
	}
	else if (type == MG4)
	{
		attack = 130;
		attack += RunningData::getInstance() ->getReinfoce().m_reinfoceSys[1].value;
		img = CCSprite::createWithSpriteFrameName("bullet31.png");
		runbulletAction();
	}
	else
	{
		attack = 20;
		img = CCSprite::create("bullet0.png");
	}

	

	img->setRotation(shootangle);
	this->addChild(img);
	bulletSpeed = 10;

	runbulletAction();

	return true;
}

void Bullet::runbulletAction()
{
	if (bulletType == VulcanM61)
	{
		CCArray *animaArray = CCArray::createWithCapacity(2);
		for (int j = 1; j <= 2; j++)
		{
			TString str;
			str += "rocketgunbullet";
			str += j;
			str += ".png";
			CCSpriteFrame *frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.1f);
		CCAnimate* animate = CCAnimate::create(animation);
		img -> runAction(CCRepeatForever::create(animate));
	}
	else if (bulletType == M107)
	{
		CCArray *animaArray = CCArray::createWithCapacity(10);
		for (int j = 1; j <= 10; j++)
		{
			TString str;
			str += "fireguneffect";
			str += j;
			str += ".png";
			CCSpriteFrame *frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
		CCAnimate* animate = CCAnimate::create(animation);
		img -> runAction(CCSequence::create(animate,CCCallFunc::create(this,callfunc_selector(Bullet::setThisBulletKilled)),NULL));
	}
	else if (bulletType == M1014)
	{
		CCArray *animaArray = CCArray::createWithCapacity(6);
		for (int j = 1; j <= 6; j++)
		{
			TString str;
			str += "jiguangEffect";
			str += j;
			str += ".png";
			CCSpriteFrame *frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
		CCAnimate* animate = CCAnimate::create(animation);
		img -> runAction(CCSequence::create(animate,CCCallFunc::create(this,callfunc_selector(Bullet::setThisBulletKilled)),NULL));
	}
	else if (bulletType == MG4)
	{
		CCArray *animaArray = CCArray::createWithCapacity(2);
		for (int j = 1; j <= 2; j++)
		{
			TString str;
			str += "bullet3";
			str += j;
			str += ".png";
			CCSpriteFrame *frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
		CCAnimate* animate = CCAnimate::create(animation);
		img -> runAction(CCRepeatForever::create(animate));
	}
}

void Bullet::touchmove(CCPoint pos,float touchangle)
{
	if (!istouchmoved)
	{
		img -> stopAllActions();
		CCArray *animaArray = CCArray::createWithCapacity(4);
		for (int j = 3; j <= 6; j++)
		{
			TString str;
			str += "fireguneffect";
			str += j;
			str += ".png";
			CCSpriteFrame *frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
		CCAnimate* animate = CCAnimate::create(animation);
		img -> runAction(CCRepeatForever::create(animate));
	}
	angle = touchangle;
	setPosition(pos);
	if (((touchangle/PI * 180) <= 90 && (touchangle/PI * 180) >=0) || ((touchangle/PI * 180) <= 360 && (touchangle/PI * 180) >=270))
	{
		img -> setRotation(touchangle/PI*180);
	}
	istouchmoved = true;
}

void Bullet::touchend()
{
	CCArray *animaArray = CCArray::createWithCapacity(6);
	for (int j = 5; j <= 10; j++)
	{
		TString str;
		str += "fireguneffect";
		str += j;
		str += ".png";
		CCSpriteFrame *frame = 
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
		animaArray->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
	CCAnimate* animate = CCAnimate::create(animation);
	img -> stopAllActions();
	img -> runAction(CCSequence::create(animate,CCCallFunc::create(this,callfunc_selector(Bullet::setThisBulletKilled)),NULL));
}

void Bullet::updata(float dt)
{
	if (bulletType != M107 && bulletType != M1014)
	{
		move(bulletSpeed * sin(angle), bulletSpeed * cos(angle));
	}
	checkCollision();
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	if (getPositionX() < -10 || getPositionY() < -10 || getPositionX() > size.width + 10 || getPositionY() > size.height + 10)
	{
		life = false;
	}
}

void Bullet::showBoom()
{
	CCArray *animaArray = CCArray::createWithCapacity(12);
	for (int j = 1; j <= 12; j++)
	{
		TString str;
		str += "rocketgunboom";
		str += j;
		str += ".png";
		CCSpriteFrame *frame = 
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
		animaArray->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.05f);
	CCAnimate* animate = CCAnimate::create(animation);
	img -> stopAllActions();
	img -> runAction(animate);
}

void Bullet::move(float xx, float yy)
{
	if (!isbooming)
	{
		setPosition(ccp(getPositionX() + xx, getPositionY() + yy));
	}
}

CCRect Bullet::getCollisionRect()
{
	CCSize size = img->getContentSize();
	//CCSize size = img -> getTexture() -> getContentSize();
	float xx = img->getPositionX();
	float yy = img->getPositionY();
	return CCRectMake(getPositionX() - size.width/2, getPositionY() - size.height/2, size.width, size.height);
}

void Bullet::checkCollision()
{
	if (iscreateForZombie)
	{
		//检测是否碰到敌人(如果碰到敌人就让清除子弹)
		if (bulletType == M107)
		{
			schedule(schedule_selector(Bullet::reduceEnemyHpEveryTwoSecond),0.1);
		}
		else if (bulletType == M1014)
		{
			schedule(schedule_selector(Bullet::reduceEnemyHpInRect),0.1);
		}
		else 
		{
			if (EnemyManage::oneself->bulletAndEnemyCollision(getCollisionRect(), this))
			{
				actionAfterCollsion();
			}
		}
	}
	else
	{
		destinationPoint = ccp(400,0);
		attackDistance = 80;
		if (ccpDistance(destinationPoint,getPosition()) <= 80)
		{
			if (type == VulcanM61)
			{
				if (!isbooming)
				{   
					isbooming = true;
					showBoom();
					scheduleOnce(schedule_selector(Bullet::setBulletKilled),boomtime);
					BattleManage::oneself -> changeHeroBlood(-120);   // 追踪者攻击
				}
			}
			else
				life = false;
		}
		
	}
	
}

void Bullet::actionAfterCollsion()
{
	if (type == VulcanM61)
	{
		if (!isbooming)
		{
			isbooming = true;
			showBoom();
			scheduleOnce(schedule_selector(Bullet::reduceEnemyHPOnce),boomtime * 0.5);  
			scheduleOnce(schedule_selector(Bullet::setBulletKilled),boomtime);
		}
	}
	else if (type == M107)
	{

	}
	else if (type == M1014)
	{

	}
	else if (type == RPG_7)
	{
		life = false;
	}
	else if (type == MG4)
	{
		if (!isbooming)
		{
			isbooming = true;
			showBoom();
			scheduleOnce(schedule_selector(Bullet::reduceEnemyHPOnce),boomtime * 0.5);  
			scheduleOnce(schedule_selector(Bullet::setBulletKilled),boomtime);
		}
	}
	else
		life = false;
}

void Bullet::reduceEnemyHpEveryTwoSecond(float dt)
{
	//
	EnemyManage::oneself -> reduceEnemyHPAngleAndDis(angle,img -> getContentSize().height,attack);
}

void Bullet::reduceEnemyHpInRect(float dt)
{
	EnemyManage::oneself -> reduceEnemyHpInRect(angle,img -> getContentSize().height,attack);
}

void Bullet::setNotForZombie()
{
	// 添加血条
	HP = currentHp = 25;

	hpSpr = CCSprite::create("hp.png");
	hpBgSpr = CCSprite::create("hpBG.png");
	hpSpr->setAnchorPoint(ccp(0, 0.5f));
	hpBgSpr->setAnchorPoint(ccp(0, 0.5f));
	hpSpr->setPosition(getPosition());
	hpBgSpr->setPosition(hpSpr->getPosition());
	hpImgWidth = hpSpr->getTextureRect().size.width;
	this -> addChild(hpBgSpr);
	this -> addChild(hpSpr);

	iscreateForZombie = false;
}

void Bullet::reduceHp(int hp)
{
	// 根据类型判断  是否变身
	if (currentHp <= 0)
	{
		return;
	}
	currentHp -= hp;
	if (currentHp <= 0)
	{
		life = false;
	}
	else
	{
		CCRect re = hpSpr->getTextureRect();
		int cc = hpImgWidth * (float)currentHp / HP;
		re.size.width = cc;
		hpSpr->setTextureRect(re);
	}
	
}

void Bullet::setBulletKilled(float dt)
{
	life = false;
}

void Bullet::reduceEnemyHPOnce(float dt)
{
	EnemyManage::oneself -> reduceEnemyHpInDistance(getPosition(),img -> getContentSize().width,attack);
}

void Bullet::setThisBulletKilled()
{
	life = false;
}

float Bullet::getATK()
{
	if (bulletType == VulcanM61)
	{
		// 范围攻击不在enemy中减少血量
		return 0;
	}
	
	return attack;
}

float Bullet::getAngle()
{
	return angle;
}

int Bullet::getBulletType()
{
	return bulletType;
}