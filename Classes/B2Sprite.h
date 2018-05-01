#pragma once
#include "cocos2d.h"
#include <Box2D/Box2D.h>
USING_NS_CC;

class B2Sprite : public CCSprite
{
public:
	CC_SYNTHESIZE(b2Body *, m_b2Body, B2Body);
	CC_SYNTHESIZE(bool, m_isDead, IsDead);
	CC_SYNTHESIZE(bool, m_isAlive, IsAlive);
};