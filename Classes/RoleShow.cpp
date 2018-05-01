#include "RoleShow.h"

void RoleShow::resetArea(const CCPoint& location, const CCSize& size)
{
	m_location = location;
	m_size = size;

	rect = CCRectMake(m_location.x+m_size.width*0.1, m_location.y, m_size.width- m_size.width*0.2, m_size.height-m_size.height*0.3);
}

bool RoleShow::init()
{
	bool bRet = false;
	if(!CCNode::init())
	{
		return bRet;
	}

	m_location = CCPointZero;
	m_size = CCSizeZero;

	bulletSpeed = 10;
	heroAngle = 2;
	m_blackBullet = 0;
	m_ironmanBullet = 0;
	m_ironmanBulletTwo = 0;

	wolfBullectIndex = 0;
	pFiregun = NULL;
	epIndexOrien = true;

	loadAnimation();

	schedule(schedule_selector(RoleShow::process));

	schedule(schedule_selector(RoleShow::roleChangeAngle),0.037f);

	schedule(schedule_selector(RoleShow::addBullet),0.3);

	bRet = true;

	return bRet;
}

void RoleShow::createBulletAtPos(float dt)
{
	CCPoint createPoint = startPoint + ccp(-5,-5);
	float tx = endPoint.x - 5;
	float ty = endPoint.y - 5;

	createBullet(m_bulletType, createPoint, ccp(tx, ty));
}

void RoleShow::createBulletAtPos2(float dt)
{
	CCPoint createPoint = startPoint + ccp(5,5);
	float tx = endPoint.x + 5;
	float ty = endPoint.y + 5;

	createBullet(m_bulletType, createPoint, ccp(tx, ty));
}

void RoleShow::createBullet(int type, const CCPoint& startPoint, const CCPoint& endPoint)
{
	Bullet* pBullet = Bullet::create(static_cast<BulletType>(type), twoPoint(startPoint, endPoint));

	pBullet->setPosition(startPoint);
	bulletList.push_back(pBullet);
	this->addChild(pBullet);
}

void RoleShow::createLaserBullet(const CCPoint& startPoint)
{
	jiguangGun = CCSprite::createWithSpriteFrameName("jiguangEffect1.png");
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
		jiguangGun -> runAction(CCSequence::create(animate,CCCallFuncN::create(this,callfuncN_selector(RoleShow::removeSelf)),NULL));
		jiguangGun->setAnchorPoint(ccp(0,0));
		jiguangGun->setPosition(ccp(startPoint.x - 25, startPoint.y-40));
		jiguangGun->setRotation(heroAngle);
		addChild(jiguangGun);
}

void RoleShow::wolverineGunAnimation()
{
	CCArray *animaArray = CCArray::createWithCapacity(3);
	for (int j = 1; j <= 3; j++)
	{
		TString str;
		str += "hero2_gun1";
		str += j;
		str += ".png";
		CCSpriteFrame *frame = 
			CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
		animaArray->addObject(frame);
	}
	CCSpriteFrame *frame = 
		CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("hero2_gun1.png");
	animaArray->addObject(frame);
	CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
	CCAnimate* animate = CCAnimate::create(animation);
	zhujiaogun -> runAction(animate);

}


void RoleShow::firegunEffect()
{

	pFiregun = CCSprite::createWithSpriteFrameName("fireguneffect1.png");

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
	pFiregun -> runAction(CCRepeatForever::create(animate));
	pFiregun->setAnchorPoint(ccp(0.5,0));
	pFiregun->setScale(0.5);

	//pFiregun->setPosition(ccp(-m_size.width*0.07,-m_size.height*0.25));

	addChild(pFiregun);
		
	//img -> setRotation(touchangle/PI*180);
}

void RoleShow::addBullet(float dt)
{
	//startPoint = ccp(m_size.width*0.1,-m_size.height*0.2);
	endPoint = CCPointZero;

	int distance = 200;
	float x =cos(CC_DEGREES_TO_RADIANS(90-heroAngle)) * distance;
	float y = sin(CC_DEGREES_TO_RADIANS(90-heroAngle)) * distance;
	endPoint = ccp(x,y);

	distance=100;
	float sx =cos(CC_DEGREES_TO_RADIANS(90-heroAngle)) * distance;
	float sy = sin(CC_DEGREES_TO_RADIANS(90-heroAngle)) * distance;
	CCPoint gunPoint = zhujiaogun->getPosition();
	startPoint = ccp(sx+gunPoint.x, sy+gunPoint.y);

	if(m_currentHero == k_battle_ironmen)
	{
		m_ironmanBullet++;
		if(m_ironmanBullet < 1)
		{
			return;
		}
		m_ironmanBullet = 0;
		m_bulletType = M1014;

		createLaserBullet(startPoint);
		
		m_ironmanBulletTwo++;
		if(m_ironmanBulletTwo <4)
		{
			return;
		}
		m_ironmanBulletTwo = 0;

		createBullet(MG4, startPoint, endPoint);
		

	} else if(m_currentHero == k_battle_blackwidow)
	{
		m_blackBullet++;
		if(m_blackBullet < 3)
		{
			return;
		}
		m_blackBullet = 0;
		m_bulletType = VulcanM61;
		createBullet(m_bulletType, startPoint, endPoint);

	} else if(m_currentHero == k_battle_wolverine)
	{
		bulletSpeed = 5;
		m_bulletType = RPG_7;
		
		wolverineGunAnimation();

		scheduleOnce(schedule_selector(RoleShow::createBulletAtPos),0.08f);
		scheduleOnce(schedule_selector(RoleShow::createBulletAtPos2),0.16f);
		createBullet(m_bulletType, startPoint, endPoint);
	}
		
	//shoot(VulcanM61, startPoint, endPoint);
}

void RoleShow::roleChangeAngle(float dt)
{
	if(heroAngleOrien)
	{
		heroAngle++;
	} else 
	{
		heroAngle--;
	}

	if(heroAngle > 30 && heroAngleOrien)
	{
		heroAngle = 30;
		heroAngleOrien = false;
	} else if(heroAngle < -30)  
	{
		heroAngle = -30;
		heroAngleOrien = true;
	}

	moveHero();
	
}

void RoleShow::process(float dt)
{

	for (unsigned int i = 0; i < bulletList.size(); ++i)
	{
		if (bulletList[i] != NULL)
		{
			Bullet* pBullet = bulletList.at(i);

			//切换角色时是否移除子弹
			int type = pBullet->getBulletType();
			if(m_currentHero == k_battle_blackwidow)
			{
				if(type != VulcanM61 && type != M107)
				{
					pBullet-> removeFromParent();
					vector<Bullet*>::iterator it = bulletList.begin() + i;
					bulletList.erase(it);

					continue;
				}
			} else if(m_currentHero == k_battle_wolverine)
			{
				if(type != RPG_7)
				{
					pBullet-> removeFromParent();
					vector<Bullet*>::iterator it = bulletList.begin() + i;
					bulletList.erase(it);

					continue;
				}
			} else if(m_currentHero == k_battle_ironmen)
			{
				if(type != M1014 && type!=MG4)
				{
					pBullet-> removeFromParent();
					vector<Bullet*>::iterator it = bulletList.begin() + i;
					bulletList.erase(it);

					continue;
				}
			}

			float angle = pBullet->getAngle();
			pBullet->move(bulletSpeed * sin(angle), bulletSpeed * cos(angle));

			CCPoint point = pBullet->getPosition();
			CCPoint boomPoint = pBullet->getParent()->convertToWorldSpace(point);
			if(!rect.containsPoint(boomPoint))
			{
				if(type == VulcanM61 || type == MG4)
				{
					showBoom(point);
				}

				pBullet-> removeFromParent();
				vector<Bullet*>::iterator it = bulletList.begin() + i;
				bulletList.erase(it);
			}
			
		}
	}

}

/*1 黑寡妇 2 金刚狼 3 钢铁侠
*/
void RoleShow::showHeroAnimation(int currentHero,const CCPoint& offsetPoint)
{
	if(currentHero == k_battle_blackwidow)
	{
		firegunEffect();
	}
	
	m_currentHero = currentHero;
	m_offsetPoint = offsetPoint;

	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	TString zhujiaoname;
	zhujiaoname += "hero";
	zhujiaoname += currentHero;
	zhujiaoname += "_middle1.png";
	zhujiao = CCSprite::create();
	zhujiao->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaoname.data()));
	zhujiao->setAnchorPoint(ccp(0.5f, 0.0f));
	//zhujiao->setPosition(ccp(x-20, y-15-offsetY));
	zhujiao->setPosition(ccp(0-offsetPoint.x, 0-offsetPoint.y));

	addChild(zhujiao, 1004);

	TString zhujiaolegname;
	zhujiaolegname += "hero";
	zhujiaolegname += currentHero;
	zhujiaolegname += "_middleleg.png";
	zhujiaoleg = CCSprite::createWithSpriteFrameName(zhujiaolegname.data());
//	zhujiaoleg -> setPosition(ccp(x, y-offsetY));
	zhujiaoleg->setAnchorPoint(ccp(0.5f, 0.0f));
	zhujiaoleg -> setPosition(ccp(20-offsetPoint.x, -15-offsetPoint.y));

	addChild(zhujiaoleg, 1002);


	//主角动画   主角 关卡信息都要根据传入的来
	TString zhujiaogunname;
	zhujiaogunname += "hero";
	zhujiaogunname += currentHero;
	zhujiaogunname += "_gun1.png";
	zhujiaogun = CCSprite::create();
	zhujiaogun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaogunname.data()));
	float anchorPointY = 20/zhujiaogun -> getContentSize().height;
	zhujiaogun->setAnchorPoint(ccp(0.5f, -anchorPointY));
	zhujiaogun->setPosition(ccp(0-offsetPoint.x, 20-offsetPoint.y));
	addChild(zhujiaogun, 1003);

	moveHero();
}


void RoleShow::changeHero(int currentHero,const CCPoint& offsetPoint)
{

	if(m_currentHero == currentHero) return;

	heroAngle = 2;
	if(currentHero == k_battle_blackwidow)
	{
		firegunEffect();
	} else
	{
		if(pFiregun)
		{
			pFiregun->stopAllActions();
			pFiregun->removeFromParent();
			pFiregun = NULL;
		}
	}

	m_currentHero = currentHero;
	m_offsetPoint = offsetPoint;

	TString zhujiaoname;
	zhujiaoname += "hero";
	zhujiaoname += currentHero;
	zhujiaoname += "_middle1.png";
	zhujiao->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaoname.data()));

	TString zhujiaolegname;
	zhujiaolegname += "hero";
	zhujiaolegname += currentHero;
	zhujiaolegname += "_middleleg.png";
	zhujiaoleg -> setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaolegname.data()));

	zhujiaogun->cleanup();
	if (currentHero != 3)
	{
		TString zhujiaogunname;
		zhujiaogunname += "hero";
		zhujiaogunname += currentHero;
		zhujiaogunname += "_gun1.png";
		zhujiaogun->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(zhujiaogunname.data()));

		zhujiaogun -> setVisible(true);
		zhujiao->setPosition(ccp(5, -offsetPoint.y));
	}
	else
	{
		zhujiaogun -> setVisible(false);
		float pY = zhujiao->getPositionY();
		zhujiao->setPosition(ccp(7, -20-offsetPoint.y));

	}

	moveHero();
}

void RoleShow::moveHero()
{
	if(m_currentHero == k_battle_blackwidow)
	{
		int distance = 60;
		float sx =cos(CC_DEGREES_TO_RADIANS(90-heroAngle)) * distance;
		float sy = sin(CC_DEGREES_TO_RADIANS(90-heroAngle)) * distance;
		CCPoint gunPoint = zhujiaogun->getPosition();
		CCPoint point = ccp(sx+gunPoint.x-10, sy+gunPoint.y);
		pFiregun->setPosition(point);
		pFiregun->setRotation(heroAngle);
	}

	zhujiaogun->setRotation(heroAngle);
	zhujiao->setRotation(heroAngle);
	
}

void RoleShow::loadAnimation()
{
	//加载主角图片与plist
	CCTextureCache::sharedTextureCache()->addImage("hero1.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero1.plist");
	CCTextureCache::sharedTextureCache()->addImage("hero2.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero2.plist");
	CCTextureCache::sharedTextureCache()->addImage("hero3.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero3.plist");

	// 加载枪支
	CCTextureCache::sharedTextureCache()->addImage("hero1gun.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero1gun.plist");
	CCTextureCache::sharedTextureCache()->addImage("hero2gun.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero2gun.plist");
	CCTextureCache::sharedTextureCache()->addImage("hero3gun.png");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("hero3gun.plist");


}

const CCPoint& RoleShow::getLocataion()
{
	return m_location;
}
const CCSize& RoleShow::getSize()
{
	return m_size;
}

void RoleShow::showBoom(const CCPoint& point)
{
	CCSprite* pBoom = CCSprite::createWithSpriteFrameName("rocketgunbullet1.png");
	pBoom->setPosition(point);
	addChild(pBoom);
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

	CCCallFuncN* funcN = CCCallFuncN::create(this,callfuncN_selector(RoleShow::removeSelf));
	CCSequence* seq = CCSequence::createWithTwoActions(animate, funcN);
	
	pBoom -> stopAllActions();
	pBoom -> runAction(seq);
}

void RoleShow::removeSelf(CCNode* pSender)
{
	pSender->removeFromParent();
}

void RoleShow::pause()
{
	this->pauseSchedulerAndActions();
}

void RoleShow::resume()
{
	this->resumeSchedulerAndActions();
}


void RoleShow::visit()
{
	
	glEnable(GL_SCISSOR_TEST);

	CCEGLView::sharedOpenGLView()->setScissorInPoints(m_location.x -  m_size.width*0.5, m_location.y, m_size.width + m_size.width*0.8, m_size.height +m_size.height*0.1 );

	CCNode::visit();
	glDisable(GL_SCISSOR_TEST);
	
}

