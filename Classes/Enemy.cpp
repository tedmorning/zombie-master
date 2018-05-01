#include "Enemy.h"
#include "tool.h"
#include "Bullet.h"
#include <List>
#include <math.h>
#include "EnemyData.h"
#include "BattleManage.h"
#include "EnemyManage.h"
#include "Bullet.h"
#include "ZombieSound.h"
using namespace std;

Enemy::Enemy():
moveSpeed(1),
movePointIndex(0),
routeIndex(0),
currentActionIndex(0),
lastActionIndex(-1),
HP(0),
currentHP(0),
pathIndex(0),
m_attack_duration(0.0)
{
	for (short i = 0; i < 4; ++i)
	{
		spriteAnimation[i] = NULL;  // 向下走 向左走 向下攻击  向左攻击       一共五个  死亡的动画在死亡时创建
	}
}

Enemy::~Enemy()
{
	
}

Enemy* Enemy::create(BattleManage *battle)
{
	Enemy* enemy = new Enemy();
	if (enemy->init(battle))
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

bool Enemy::init(BattleManage *battle)
{
	this->battle = battle;
	life = true;  
	isBulletThrough = false;
	duration = 0.0;
	return true;
}

void Enemy::updata(float dt)
{
	// 根据类型判断
	
	switch (state)
	{
	case Walk:
		{
			moveZombie();
			changeMoveState();
		}
		break;
	case Attack:
		{
			switch(zombieType)
			{
			case ZombieOrdinary:      // 普通攻击  播放攻击动画  没有攻击效果
			case ZombieDog:
			case ZombieShield:
			case ZombieGiant:
			case ZombieTyrantState2:
			case ZombieScholar:
			case ZombieTrackerState2:
			case ZombieGeneralState2:
				{
					duration += dt;
					runAttackAction();
					if (duration >= m_attack_duration)
					{
						BattleManage::oneself -> changeHeroBlood(-m_attack_count);
						showSpecialAttackAction();
						duration = 0.0;
						playSound("music/zombiehit.ogg");
					}
				}
				break;
			case ZombieBomb:
				{
					//播放爆炸动画  之后再减血量  死亡动画
					reduceHp(currentHP);
					runAttackAction();
					playSound("music/zombiehit.ogg");
					BattleManage::oneself -> changeHeroBlood(-m_attack_count);
					duration = 0.0;
				}
				break;
			case ZombieSoldiers:
				{
					duration += dt;
					runAttackAction();
					if (duration >= m_attack_duration)
					{
						playSound("music/zombiehit.ogg");
						showSpecialAttackAction();
						duration = 0.0;
					}
				}
				break;
			case ZombieDoctor:
				{
					duration += dt;
					if (duration >= m_attack_duration)
					{
						runAttackAction();
						duration = 0.0;
					}
					if (!iscuring)
					{
						iscuring = true;
						schedule(schedule_selector(Enemy::cureOtherZombie),1.0f);
						schedule(schedule_selector(Enemy::showCureAnimation),5.0f);
					}
				}
				break;
			case ZombieTracker:
			case ZombieMaster:
			case ZombieBiochemical:
				{
					duration += dt;
					if (duration > m_attack_duration)
					{
						playSound("music/zombiehit.ogg");
						duration = 0.0;
						showSpecialAttackAction();
					}
				}
				break;
			case ZombieGeneral:
			case ZombieTyrant:
				{
					duration += dt;
					runAttackAction();
					if (duration >= m_attack_duration)
					{
						playSound("music/zombiehit.ogg");
						showSpecialAttackAction();
						duration = 0.0;
					}
				}
				break;
			}
		}
		break;
	case Cure:
		{
		}
		break;
	case Move:
		{
			showMoveAnimation();
		}
		break;
	case Call:
		{
			showCallAnimation();
		}
		break;
	case Death:
		deathHandle();
		break;
	}
}

void Enemy::runAttackAction()
{
	// 攻击动作
	if (zombieType == ZombieSoldiers || zombieType == ZombieDoctor)
	{
		if (spriteAnimation[2])
		{
			spriteAnimation[2]->setVisible(true);
			currentActionIndex = 2;
		}
		return;
	}

	switch (moveOrien)
	{
	case UpMove:
		break;
	case DownMove:
		if (spriteAnimation[2])
		{
			spriteAnimation[2]->setVisible(true);
			currentActionIndex = 2;
		}
		break;
	case LeftMove:
		if (spriteAnimation[3])
		{
			spriteAnimation[3]->setVisible(true);
			spriteAnimation[3]->setScaleX(-1);
			currentActionIndex = 3;
		}
		break;
	case RightMove:
		if (spriteAnimation[3])
		{
			spriteAnimation[3]->setVisible(true);
			currentActionIndex = 3;
		}
		break;
	}
	//moveOrien = Situ;
	return;
}

void Enemy::showSpecialAttackActionDelay(float dt)
{
	if (state == Death)
	{
		return;
	}

	if (zombieType == ZombieGeneral)
	{
		CCArray *animaArray = CCArray::createWithCapacity(3);
		for (int j = 1; j <= 3; j++)
		{
			TString str;
			str += "zombie12attackeffect";
			str += j;
			str += ".png";
			CCSpriteFrame *frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.05f);
		CCAnimate* animate = CCAnimate::create(animation);

		CCSprite* attack = CCSprite::createWithSpriteFrameName("zombie12attackeffect1.png");
		attack -> setPosition(ccp(getPositionX() + 15,getPositionY() - 50));
		battle -> addChild(attack,getZOrder());
		attack->setRotation(twoPoint(attack -> getPosition(),ccp(400,60))/PI*180);
		attack -> runAction(CCSequence::create(CCSpawn::create(animate, CCMoveTo::create(0.2,ccp(400,60)),NULL),CCCallFuncO::create(this,callfuncO_selector(Enemy::removeChildByObject),attack),NULL));
	}
}

void Enemy::showSpecialAttackAction()
{
	// 攻击效果   如：远程激光
	switch(zombieType)
	{
	case ZombieSoldiers:
		{
			// 走的方向不同激光位置不同
			CCSprite* attack = CCSprite::createWithSpriteFrameName("zombie5bullet.png");
			attack -> setPosition(getPosition());
			battle -> addChild(attack,getZOrder());
			attack->setRotation(twoPoint(attack -> getPosition(),ccp(400,60))/PI*180);
			attack -> runAction(CCSequence::create(CCMoveTo::create(0.2,ccp(400,60)),CCCallFuncO::create(this,callfuncO_selector(Enemy::removeChildByObject),attack),NULL));
		}
		break;
	case ZombieTyrant:
		{
			// 走的方向不同激光位置不同
			CCSprite* attack = CCSprite::createWithSpriteFrameName("9_attack.png");
			attack -> setAnchorPoint(ccp(0.5,1.0));
			switch(moveOrien)
			{
			case DownMove:
				{
					attack -> setPosition(getPosition());
				}
				break;
			case LeftMove:
				{
					attack -> setPosition(getPosition());
				}
				break;
			case RightMove:
				{
					attack -> setPosition(getPosition());
				}
				break;
			}
			battle -> addChild(attack,getZOrder());
			attack->setRotation(twoPoint(attack -> getPosition(),ccp(400,60))/PI*180);
			attack -> runAction(CCSequence::create(CCMoveTo::create(0.2,ccp(400,60)),CCCallFuncO::create(this,callfuncO_selector(Enemy::removeChildByObject),attack),NULL));
		}
		break;
	case ZombieTracker:
		{
			////创建n个可拦截火箭弹  
			//Bullet* bullet = Bullet::create(VulcanM61,twoPoint(getPosition(),ccp(400,0)));
			//bullet -> setPosition(getPosition());
			//bullet -> setNotForZombie();
			//battle -> firearms ->bulletList.push_back(bullet);   // 渣
			//battle -> addChild(bullet,getZOrder());
			CCSprite* attack = CCSprite::createWithSpriteFrameName("zombie15bullet.png");
			attack -> setPosition(getPosition());
			battle -> addChild(attack,getZOrder());
			attack->setRotation(twoPoint(attack -> getPosition(),ccp(400,60))/PI*180);
			attack -> runAction(CCSequence::create(CCMoveTo::create(0.2,ccp(400,60)),CCCallFuncO::create(this,callfuncO_selector(Enemy::removeChildByObject),attack),NULL));
		}
		break;
	case ZombieBiochemical:
		{
			CCArray *animaArray = CCArray::createWithCapacity(3);
			for (int j = 1; j <= 3; j++)
			{
				TString str;
				str += "13fireball";
				str += j;
				str += ".png";
				CCSpriteFrame *frame = 
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
				animaArray->addObject(frame);
			}
			CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.05f);
			CCAnimate* animate = CCAnimate::create(animation);

			CCSprite* attack = CCSprite::createWithSpriteFrameName("13fireball1.png");
			attack -> setPosition(getPosition());
			battle -> addChild(attack,getZOrder());
			attack->setRotation(twoPoint(attack -> getPosition(),ccp(400,60))/PI*180);
			attack -> runAction(CCSequence::create(CCSpawn::create(animate, CCMoveTo::create(0.2,ccp(400,60)),NULL),CCCallFuncO::create(this,callfuncO_selector(Enemy::removeChildByObject),attack),NULL));
		}
		break;
	case ZombieGeneral:
		{
			scheduleOnce(schedule_selector(Enemy::showSpecialAttackActionDelay),0.35);
		}
		break;
	}
}

void Enemy::removeChildByObject(CCObject* pSender)
{
	CCSprite* sp = (CCSprite*)pSender;
	if (sp)
	{
		BattleManage::oneself -> changeHeroBlood(-m_attack_count);
		if (zombieType == ZombieTyrant)
		{
			CCSprite* attack = CCSprite::createWithSpriteFrameName("9_attack_1.png");
			attack -> setPosition(ccp(400,60));
			battle -> addChild(attack,getZOrder());
			CCArray *animaArray = CCArray::createWithCapacity(2);
			for (int j = 1; j <= 2; j++)
			{
				TString str;
				str += "9_attack_";
				str += j;
				str += ".png";
				CCSpriteFrame *frame = 
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
				animaArray->addObject(frame);
			}
			CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
			CCAnimate* animate = CCAnimate::create(animation);
			attack -> runAction(CCSequence::create(CCRepeat::create(animate,2) ,CCCallFuncO::create(this,callfuncO_selector(Enemy::removeChildOnly),attack),NULL));
		}
		else if (zombieType == ZombieTracker)
		{
			CCSprite* attack = CCSprite::createWithSpriteFrameName("rocketgunboom1.png");
			attack -> setPosition(ccp(400,60));
			battle -> addChild(attack,getZOrder());
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
			CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
			CCAnimate* animate = CCAnimate::create(animation);
			attack -> runAction(CCSequence::create(animate,CCCallFuncO::create(this,callfuncO_selector(Enemy::removeChildOnly),attack),NULL));
		}
		sp -> removeFromParent();
	}
}

void Enemy::removeChildOnly(CCObject* pSender)
{
	CCSprite* sp = (CCSprite*)pSender;
	if (sp)
		sp -> removeFromParent();
}

void Enemy::deathHandle()
{
	if (!life)
		return;
	CCSprite * spr = spriteAnimation[ZombieAnimationQuantity - 1];

	spr->setOpacity(spr->getOpacity() - 5 > 0 ? spr->getOpacity() - 5 : 0);
	if (spr->getOpacity() <= 0)
	{
		life = false;
	}
}

void Enemy::buildZombie(short type, short routeId)
{
	zombieType = (ZombieType)type;
	routeIndex = routeId;
	// 根据僵尸类型初始化僵尸属性   在更新位置、攻击、死亡、状态转换也对僵尸类型进行判断
	HP = currentHP = ZombieBlood(zombieType);
	m_attack_count = ZombieAttack(zombieType);
	m_attack_duration = ZombieAttackDuration(zombieType);
	moveSpeed = ZombieSpeed(zombieType);
	m_current_worth_gold = ZombieWorthGold(zombieType);
	isFirstAttacked = false;
	iscuring = false;
	state = Walk;

	buildAnimation();

	// 根据僵尸种类schedule一些方法
	switch(zombieType)
	{
	case ZombieMaster:
		{
			scheduleOnce(schedule_selector(Enemy::callOtherZombie),4.0f);
			//scheduleOnce(schedule_selector(Enemy::callOtherZombieOver),8.0f);
		}
		break;
	case ZombieScholar:
		{
			scheduleOnce(schedule_selector(Enemy::callOtherZombie),3.0f);
			//scheduleOnce(schedule_selector(Enemy::callOtherZombieOver),8.0f);
		}
		break;
	case ZombieGeneral:
		{
			scheduleOnce(schedule_selector(Enemy::callOtherZombie),4.0);
			scheduleOnce(schedule_selector(Enemy::stopCallZombie),7.0f);
		}
		break;
	case ZombieBiochemical:
		{
			scheduleOnce(schedule_selector(Enemy::startCureZombie),6.0);
		}
		break;
	}
	
	setPosition(ccp(EnemyData::data->routeStartPoint[routeIndex].y * 40 + 20,
		(mapCol - 1 - EnemyData::data->routeStartPoint[routeIndex].x) * 40 + 20));
	//创建血条
	buildHpImage();
	//寻路  路线赋值会导致路径缺失
	pathData = EnemyData::data->getRoute(routeIndex);
	pathIndex = pathData->pathData.size() - 1;
	changeAnimation();
}

void Enemy::buildAnimation()
{
	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	for (short i = 0; i < ZombieAnimationQuantity-1; ++i)
	{
		//从缓存中读动画.                                                                                                                                                                   
		CCAnimation* anamtion = CCAnimationCache::sharedAnimationCache()->animationByName(AnimationName(zombieType, i).data());
		if (anamtion)
		{
			//创建动画
			animate[i] = CCAnimate::create(anamtion);
			//获取此动画第一次图片的名字就从缓存中取出
			CCSpriteFrame* frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ZombieImageName(zombieType, i, 1).data());

			spriteAnimation[i] = CCSprite::create();
			spriteAnimation[i]->setDisplayFrame(frame);
			spriteAnimation[i]->runAction(CCRepeatForever::create(animate[i]));

			addChild(spriteAnimation[i]);
			spriteAnimation[i]->setVisible(false);
		}
	}
}

void Enemy::buildDeathAnimation()
{
	switch(zombieType)
	{
		case ZombieOrdinary:
		case ZombieDog:
		case ZombieBomb:
		case ZombieShield:
		case ZombieSoldiers:
		case ZombieDoctor:
		case ZombieMaster:
		case ZombieGiant:
		case ZombieScholar:
		case ZombieBiochemical:
			{
				playSound("music/zombiedead.ogg");
				char name[100] = "";
				//从缓存中读动画.                                                                                                                                                                   
				CCAnimation* anamtion = CCAnimationCache::sharedAnimationCache()->animationByName(AnimationName(zombieType, 
					ZombieAnimationQuantity - 1).data());
				//创建动画
				animate[ZombieAnimationQuantity - 1] = CCAnimate::create(anamtion);

				//获取此动画第一次图片的名字就从缓存中取出
				CCSpriteFrame* frame = 
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(ZombieImageName(zombieType, 
					ZombieAnimationQuantity - 1, 1).data());

				spriteAnimation[ZombieAnimationQuantity - 1] = CCSprite::create();
				spriteAnimation[ZombieAnimationQuantity - 1]->setDisplayFrame(frame);
				spriteAnimation[ZombieAnimationQuantity - 1]->runAction(animate[ZombieAnimationQuantity - 1]);

				addChild(spriteAnimation[ZombieAnimationQuantity - 1]);
				spriteAnimation[ZombieAnimationQuantity - 1]->setVisible(true);
			}
			break;
		case ZombieTyrantState2:
		case ZombieTrackerState2:
		case ZombieGeneralState2:
			{
				playSound("music/bossdead.ogg");

				CCSpriteFrame* frame = 
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("rocketgunboom1.png");
				spriteAnimation[ZombieAnimationQuantity - 1] = CCSprite::create();
				spriteAnimation[ZombieAnimationQuantity - 1]->setDisplayFrame(frame);
				
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

				spriteAnimation[ZombieAnimationQuantity - 1]->runAction(animate);

				addChild(spriteAnimation[ZombieAnimationQuantity - 1]);
				spriteAnimation[ZombieAnimationQuantity - 1]->setVisible(true);
			}
			break;
		default:
			break;
	}
}

void Enemy::buildHpImage(bool created)
{
	if (created)
	{
		hpBgSpr -> removeFromParent();
		hpSpr -> removeFromParent();
	}
	hpSpr = CCSprite::create("hp.png");
	hpBgSpr = CCSprite::create("hpBG.png");
	hpSpr->setAnchorPoint(ccp(0, 0.5f));
	hpBgSpr->setAnchorPoint(ccp(0, 0.5f));
	hpSpr->setPosition(HpOffset(zombieType) + getPosition());
	hpBgSpr->setPosition(hpSpr->getPosition());
	battle->addChild(hpSpr, HP_Zorder);
	battle->addChild(hpBgSpr, HP_Zorder - 1);
	hpImgWidth = hpSpr->getTextureRect().size.width;
}


void Enemy::setNextPoint()
{
	if (pathIndex == 0)
	{
		switch (moveOrien)
		{
		case UpMove:
			break;
		case DownMove:
			if (spriteAnimation[2])
			{
				spriteAnimation[2]->setVisible(true);
				currentActionIndex = 2;
			}
			break;
		case LeftMove:
			if (spriteAnimation[3])
			{
				spriteAnimation[3]->setVisible(true);
				spriteAnimation[3]->setScaleX(-1);
				currentActionIndex = 3;
			}
			break;
		case RightMove:
			if (spriteAnimation[3])
			{
				spriteAnimation[3]->setVisible(true);
				currentActionIndex = 3;
			}
			break;
		}
		moveOrien = Situ;
		return;
	}

	if (pathData->pathData[pathIndex].x == pathData->pathData[pathIndex - 1].x) //判断行是否相同
	{
		if (pathData->pathData[pathIndex].y < pathData->pathData[pathIndex - 1].y)
		{//往右边走
			moveOrien = RightMove;
		}
		else if (pathData->pathData[pathIndex].y > pathData->pathData[pathIndex - 1].y)
		{//往左边走
			moveOrien = LeftMove;
		}
	}
	else if (pathData->pathData[pathIndex].y == pathData->pathData[pathIndex - 1].y) //判断是列是否相同
	{
		if (pathData->pathData[pathIndex].x > pathData->pathData[pathIndex - 1].x)
		{//往上边走
			moveOrien = UpMove;
		}
		else if (pathData->pathData[pathIndex].x < pathData->pathData[pathIndex - 1].x)
		{//往下边走
			moveOrien = DownMove;
		}
	}
	nextPoint.x = pathData->pathData[pathIndex - 1].y * 40 + 20;
	nextPoint.y = (mapCol - 1 - pathData->pathData[pathIndex - 1].x) * 40 + 20;
	pathIndex--;
}

void Enemy::moveZombie()
{
	if ((zombieType == ZombieTyrant  && ( ccpDistance(getPosition(),ccp(400,20)) < 250)) || (zombieType == ZombieTracker &&  ( ccpDistance(getPosition(),ccp(400,20)) < 300))
		|| (zombieType == ZombieGeneral && ( ccpDistance(getPosition(),ccp(400,20)) < 250)) || (zombieType == ZombieSoldiers && ( ccpDistance(getPosition(),ccp(400,20)) < 300))
		|| (zombieType == ZombieDoctor && ( ccpDistance(getPosition(),ccp(400,20)) < 250)) || (zombieType == ZombieScholar && ( ccpDistance(getPosition(),ccp(400,20)) < 250))
		|| (zombieType == ZombieBiochemical && ( ccpDistance(getPosition(),ccp(400,20)) < 250)))
	{
		if (spriteAnimation[currentActionIndex] && zombieType != ZombieTyrant && zombieType != ZombieScholar && zombieType != ZombieBiochemical && zombieType != ZombieGeneral && zombieType != ZombieTracker)    // 没有攻击动作的就当前动画
		{
			spriteAnimation[currentActionIndex] -> setVisible(false);
		}
		state = Attack;
		return;   // 到了可攻击位置  不移动
	}
	float xx = 0;
	float yy = 0;
	switch (moveOrien)
	{
	case UpMove:
		break;
	case DownMove:
		yy -= moveSpeed;
		break;
	case LeftMove:
		xx -= moveSpeed;
		break;
	case RightMove:
		xx += moveSpeed;
		break;
	case Situ:
		state = Attack;
		return;
	}
	move(xx, yy);
}

void Enemy::changeMoveState()
{//根据当前僵尸移动的方向来判断是否移到到终点
	switch (moveOrien)
	{
	case UpMove:
		break;
	case DownMove:
		if (getPositionY() <= nextPoint.y/*ZombieRoute(routeIndex, movePointIndex).y*/)
		{
			spriteAnimation[0]->setVisible(false);
			changeAnimation();
		}
		break;
	case LeftMove:
		if (getPositionX() <= nextPoint.x/*ZombieRoute(routeIndex, movePointIndex).x*/)
		{
			spriteAnimation[1]->setVisible(false);
			changeAnimation();
		}
		break;
	case RightMove:
		if (getPositionX() >= nextPoint.x/*ZombieRoute(routeIndex, movePointIndex).x*/)
		{
			spriteAnimation[1]->setVisible(false);
			changeAnimation();
		}
		break;
	case Situ:
		state = Attack;
		break;
	}
}

void Enemy::changeAnimation()
{
	//把僵尸隐藏，下面根据方向在显示另一个动画
	spriteAnimation[currentActionIndex]->setVisible(false);
	
	//设置下一个移动位置
	setNextPoint();

	//设置僵尸移动的动画
	switch (moveOrien)
	{
	case UpMove:
		break;
	case DownMove:
		if (spriteAnimation[0])
		{
			spriteAnimation[0]->setVisible(true);
			currentActionIndex = 0;
		}
		break;
	case LeftMove:
		if (spriteAnimation[1])
		{
			spriteAnimation[1]->setVisible(true);
			currentActionIndex = 1;
		}
		break;
	case RightMove:
		if (spriteAnimation[1])
		{
			spriteAnimation[1]->setVisible(true);
			spriteAnimation[1]->setScaleX(-1);
			currentActionIndex = 1;
		}
		break;
	case Situ:
		break;
	}

	movePointIndex++;
}

void Enemy::setPositions(CCPoint point)
{

}

void Enemy::move(float x, float y)
{
	if (hpSpr != NULL)
	{
		hpSpr->setPosition(ccp(hpSpr->getPositionX() + x, hpSpr->getPositionY() + y));
		hpBgSpr->setPosition(ccp(hpBgSpr->getPositionX() + x, hpBgSpr->getPositionY() + y));
	}
	setPosition(getPositionX() + x, getPositionY() + y);
}

void Enemy::reduceHp(float value)
{
	// 根据类型判断  是否变身
	if (currentHP <= 0)
	{
		return;
	}
	currentHP -= value;
	if (currentHP > HP)
	{
		currentHP = HP;
	}
	if (currentHP <= 0)
	{
		switch(zombieType)
		{
		case ZombieTyrant:
			{
				playSound("music/bossdeformation.ogg");
				// 变身  修改zombie状态
				zombieType = ZombieTyrantState2;
				HP = currentHP = ZombieBlood(zombieType);
				m_attack_count = ZombieAttack(zombieType);
				m_attack_duration = ZombieAttackDuration(zombieType);
				moveSpeed = ZombieSpeed(zombieType);
				m_current_worth_gold = ZombieWorthGold(zombieType);
				rebuildAnimation();
				state = Walk;
			}
			break;
		case ZombieTracker:
			{
				playSound("music/bossdeformation.ogg");
				// 变身  修改zombie状态
				zombieType = ZombieTrackerState2;
				HP = currentHP = ZombieBlood(zombieType);
				m_attack_count = ZombieAttack(zombieType);
				m_attack_duration = ZombieAttackDuration(zombieType);
				moveSpeed = ZombieSpeed(zombieType);
				m_current_worth_gold = ZombieWorthGold(zombieType);
				rebuildAnimation();
				state = Walk;
			}
			break;
		case ZombieGeneral:
			{
				playSound("music/bossdeformation.ogg");
				// 变身  修改zombie状态
				zombieType = ZombieGeneralState2;
				HP = currentHP = ZombieBlood(zombieType);
				m_attack_count = ZombieAttack(zombieType);
				m_attack_duration = ZombieAttackDuration(zombieType);
				moveSpeed = ZombieSpeed(zombieType);
				m_current_worth_gold = ZombieWorthGold(zombieType);
				rebuildAnimation();
				state = Walk;
			}
			break;
		default:
			{
				currentHP = 0;
				spriteAnimation[currentActionIndex]->setVisible(false);
				buildDeathAnimation();
				currentActionIndex = ZombieAnimationQuantity - 1;
				state = Death;
				hpSpr -> setVisible(false);
				hpBgSpr -> setVisible(false);
				battle->buildGold(m_current_worth_gold, getPosition());
				battle -> getTotalGold += m_current_worth_gold;
				battle -> killedTotalZombie ++;
			}
			break;
		}
	}
	else
	{
		updataHpSprite();
		if (!isFirstAttacked && zombieType == ZombieDoctor)
		{
			//isFirstAttacked = true;
			//schedule(schedule_selector(Enemy::cureOtherZombie),1.0f);
		}
		if (zombieType == ZombieBiochemical)
		{
			//state = Attack;
			if (state == Walk)
			{
				showMomentMoveAction();
			}
		}
	}
}

void Enemy::updataHpSprite()
{
	CCRect re = hpSpr->getTextureRect();
	int cc = hpImgWidth * (float)currentHP / HP;
	re.size.width = cc;
	hpSpr->setTextureRect(re);
}

CCRect Enemy::getCollisionRect()
{
	CCSize size = getContentSize();
	return CCRectMake(getPositionX() - size.width / 4, getPositionY() - size.height / 4, size.width/2, size.height/2);
}

bool Enemy::checkCollision(CCRect rect, Bullet* bullet)
{
	if (state == Death)
		return false;

	CCSize size = spriteAnimation[0]->getContentSize();
	if (isRectCollsion(rect.origin.x, rect.origin.y, rect.size.width, rect.size.height,
		getPositionX() - size.width / 2, getPositionY() - size.height / 2, size.width, size.height) && bullet -> life)
	{
		if (bullet ->getBulletType() != MG4)
		{
			reduceHp(bullet->getATK());
		}
		return true;
	}
	return false;
}

void Enemy::startCureZombie(float dt)
{
	if (state == Death || state == Attack)
	{
		return;
	}
	schedule(schedule_selector(Enemy::cureOtherZombie),1.0);
	scheduleOnce(schedule_selector(Enemy::stopCureOtherZombie),5.0);
}

void Enemy::cureOtherZombie(float dt)
{
	// 遍历EnemyManage中的Enemy 根据距离添加回血
	//schedule(schedule_selector(Enemy::cureOtherZombie),1.0f);
	if (state == Death || state == Attack)
	{
		return;
	}

	playSound("music/treat.ogg");
	int cureNum = 0;
	int distance = 0;
	if (zombieType == ZombieBiochemical)
	{
		cureNum = 100;
		distance = 300;
		state = Cure;
		showCureAnimation(0.0);
	}
	else
	{
		distance = 100;
		cureNum = 2;
	}
	EnemyManage::oneself -> cureZombieInDistance(getPosition(),distance,cureNum);
}

void Enemy::stopCureOtherZombie(float dt)
{
	if (state == Death)
	{
		return;
	}
	
	unschedule(schedule_selector(Enemy::cureOtherZombie));
	unschedule(schedule_selector(Enemy::showCureAnimation));
	state = Walk;
	changeMoveState();
}

void Enemy::rebuildAnimation()
{
	for (int i = 0;i < 4;i++)
	{
		if(spriteAnimation[i])
			spriteAnimation[i] -> setVisible(false);
	}
	buildAnimation();
	changeAnimation();
	updataHpSprite();
}

void Enemy::callOtherZombie(float dt)
{
	if (state == Death)
	{
		return;
	}
	playSound("music/summon.ogg");

	// 根据当前僵尸信息 重新生成其他种类的僵尸
	EnemyManage::oneself -> showCallAnimation(this);
	state = Call;
	if (zombieType != ZombieGeneral)
	{
		scheduleOnce(schedule_selector(Enemy::resetZombieWalk),1.0);
		scheduleOnce(schedule_selector(Enemy::callOtherZombieOver),1.0);
	}
	else
	{
		scheduleOnce(schedule_selector(Enemy::resetZombieWalk),0.1);
		scheduleOnce(schedule_selector(Enemy::callOtherZombieOver),0.1);
	}
}

void Enemy::callOtherZombieOver(float dt)
{
	if (state == Death)
	{
		return;
	}
	//state = Walk;
	switch(zombieType)
	{
	case ZombieMaster:
		{
			scheduleOnce(schedule_selector(Enemy::callOtherZombie),8.0f);
			//scheduleOnce(schedule_selector(Enemy::callOtherZombieOver),8.0f);
		}
		break;
	case ZombieScholar:
		{
			scheduleOnce(schedule_selector(Enemy::callOtherZombie),1.0f);
			//scheduleOnce(schedule_selector(Enemy::callOtherZombieOver),8.0f);
		}
		break;
	case ZombieGeneral:
		{
			scheduleOnce(schedule_selector(Enemy::callOtherZombie),0.66);
			//scheduleOnce(schedule_selector(Enemy::callOtherZombieOver),8.0f);
		}
		break;
	}
	//unschedule(schedule_selector(Enemy::callOtherZombie));
}

void Enemy::stopCallZombie(float dt)
{
	if (state == Death)
	{
		return;
	}
	unschedule(schedule_selector(Enemy::callOtherZombie));
	state = Walk;
}

void Enemy::resetZombieWalk(float dt)
{
	if (state == Death)
	{
		return;
	}
	state = Walk;
}

void Enemy::showMomentMoveAction()
{
	if (state != Death && state != Cure)
	{
		TString strName;
		TString str1;
		if (moveOrien == DownMove)
		{
			strName += "13downmove";
			str1 += "13downmove";
		}
		else 
		{
			strName += "13leftmove";
			str1 += "13leftmove";
		}
		str1 += "1.png";
		CCSprite* move = CCSprite::createWithSpriteFrameName(str1.data());
		CCArray *animaArray = CCArray::createWithCapacity(4);
		for (int j = 1; j <= 4; j++)
		{
			TString str;
			str += strName.data();
			str += j;
			str += ".png";
			CCSpriteFrame *frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
		CCAnimate* animate = CCAnimate::create(animation);
		move -> runAction(CCSequence::create(animate,CCCallFuncO::create(this,callfuncO_selector(Enemy::removeSprite),move),NULL));
		addChild(move);
		scheduleOnce(schedule_selector(Enemy::momentMoveZombie),0.15);
		if (spriteAnimation[currentActionIndex])
		{
			spriteAnimation[currentActionIndex] -> setVisible(false);
		}
	}
}

void Enemy::momentMoveZombie(float dt)
{
	// 根据当前僵尸信息  设置nextpoint  route 3有些问题 
	hpSpr->setPosition(ccpAdd(hpSpr -> getPosition(),ccpSub(getNextPoint(),getPosition())));
	hpBgSpr->setPosition(ccpAdd(hpBgSpr -> getPosition(),ccpSub(getNextPoint(),getPosition())));
	setPosition(getNextPoint());
	changeMoveState();
}

void Enemy::showCureAnimation(float dt)
{
	if (state == Death)
	{
		return;
	}
	// 播放完remove
	if (zombieType == ZombieDoctor)
	{
		CCSprite* cure = CCSprite::createWithSpriteFrameName("cureanimation1.png");
		CCArray *animaArray = CCArray::createWithCapacity(8);
		for (int j = 1; j <= 8; j++)
		{
			TString str;
			str += "cureanimation";
			str += j;
			str += ".png";
			CCSpriteFrame *frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
		CCAnimate* animate = CCAnimate::create(animation);
		cure -> runAction(CCSequence::create(animate,CCCallFuncO::create(this,callfuncO_selector(Enemy::removeSprite),cure),NULL));
		addChild(cure);
	}
	else if (zombieType == ZombieBiochemical)
	{
		TString strName;
		TString str1;
		if (moveOrien == DownMove)
		{
			strName += "13downcure";
			str1 += "13downcure";
		}
		else 
		{
			strName += "13leftcure";
			str1 += "13leftcure";
		}
		str1 += "1.png";
		CCSprite* cure = CCSprite::createWithSpriteFrameName(str1.data());
		CCArray *animaArray = CCArray::createWithCapacity(2);
		for (int j = 1; j <= 2; j++)
		{
			TString str;
			str += strName.data();
			str += j;
			str += ".png";
			CCSpriteFrame *frame = 
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str.data());
			animaArray->addObject(frame);
		}
		CCAnimation* animation = CCAnimation::createWithSpriteFrames(animaArray, 0.07f);
		CCAnimate* animate = CCAnimate::create(animation);
		cure -> runAction(CCSequence::create(animate,CCCallFuncO::create(this,callfuncO_selector(Enemy::removeSprite),cure),NULL));
		addChild(cure);
		if (spriteAnimation[currentActionIndex])
		{
			spriteAnimation[currentActionIndex] -> setVisible(false);
		}
	}
}

void Enemy::showMoveAnimation()
{

}

void Enemy::showCallAnimation()
{

}

void Enemy::removeSprite(CCObject* pSender)
{
	CCSprite* temp = (CCSprite*)pSender;
	if (temp)
	{
		temp -> removeFromParent();
	}

	if (spriteAnimation[currentActionIndex])
	{
		spriteAnimation[currentActionIndex] -> setVisible(true);
	}
}

void Enemy::setHP(float value)
{
	HP = HP*value;
	currentHP = HP;
}
