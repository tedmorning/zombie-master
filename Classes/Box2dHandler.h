#pragma once
#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "B2Sprite.h"
USING_NS_CC;

class Box2dHandler : public CCNode, public b2ContactListener
{
public:
	b2World *m_world;

	bool initBox2D();

	void addBodyForSprite(B2Sprite *sprite, double density = 10.0);

	void addFixtureForSprite(B2Sprite *sprite, double density = 10.0);

	void dealCollisions();

	virtual void BeginConact(b2Contact *cantact);

	virtual void EndConact(b2Contact *cantact);

	static Box2dHandler* handler();

	bool init();

	//virtual void draw();

	virtual void update(float dt);
};