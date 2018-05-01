#include "GoldAnimation.h"
#include "tool.h"
#include "TString.h"
#include "BattleManage.h"

bool GoldAnimation::init()
{
	//gold = CCSprite::create("jinBiIcon.png");
	spr = CCSprite::create("+.png");
	spr2 = CCSprite::create("$.png");
	spr->setPosition(ccp(-25, 0));
	addChild(spr);
	addChild(spr2);
	life = true;

	//注册自定义的更新函数
	this->scheduleUpdate();
	return true;
}

void GoldAnimation::update(float delta)
{
	CCNode::update(delta);
	setPosition(ccp(getPositionX(), getPositionY() + 2));
	
	for (short i = 0; i < numberLength; ++i)
	{
		number[i]->setOpacity(number[i]->getOpacity() - 5 <= 0 ? 0 : number[i]->getOpacity() - 5);
	}
	spr->setOpacity(number[0]->getOpacity());
	spr2->setOpacity(number[0]->getOpacity());
	if (number[0]->getOpacity() <= 0)
	{
		life = false;
		BattleManage::oneself->deleteGold(this);
	}
}

void GoldAnimation::setGoldQuantity(short goldNumber)
{
	TString str;
	str += goldNumber;
	goldQuantity = goldNumber;
	numberLength = countIntNumber(goldNumber);

	number = new CCSprite*[numberLength];
	CCSprite *sp = CCSprite::create("number1.png");
	for (short i = 0; i < numberLength; ++i)
	{
		number[i] = CCSprite::create("number1.png");
		CCRect rect = number[i]->getTextureRect();
		rect.origin.x = (str[i] - 48) * 25;
		rect.size.width = 25;
		number[i]->setTextureRect(rect);
		number[i]->setPosition(ccp(i*25, 0));
		addChild(number[i]);
	}
	spr2->setPosition(ccp(numberLength * 25, 0));
}