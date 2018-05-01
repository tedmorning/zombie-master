#include "Box2dHandler.h"
#include "tool.h"

Box2dHandler* Box2dHandler::handler()
{
	static Box2dHandler* handle = NULL;
	if (handle == NULL)
	{
		handle = new Box2dHandler();
		handle->init();
		return handle;
	}
	else
	{
		return handle;
	}
}

bool Box2dHandler::init()
{
	this->initBox2D();
	this->scheduleUpdate();
	return true;
}

bool Box2dHandler::initBox2D()
{
	CCSize s = CCDirector::sharedDirector()->getVisibleSize();

	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(false);
	m_world->SetContactListener(this);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);

	b2Body * groundBody = m_world->CreateBody(&groundBodyDef);

	//定交边缘形状
	b2EdgeShape groundBox;

	//底部
	groundBox.Set(b2Vec2(0, 0), b2Vec2(s.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);

	//顶部
	groundBox.Set(b2Vec2(0, s.height / PTM_RATIO), b2Vec2(s.width / PTM_RATIO, s.height / PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);

	//左侧
	groundBox.Set(b2Vec2(0, s.height / PTM_RATIO), b2Vec2(0, 0));
	groundBody->CreateFixture(&groundBox, 0);

	//右侧
	groundBox.Set(b2Vec2(s.width / PTM_RATIO, s.height / PTM_RATIO), b2Vec2(s.width / PTM_RATIO, 0));
	groundBody->CreateFixture(&groundBox, 0);
	return true;
}

void Box2dHandler::addFixtureForSprite(B2Sprite *sprite, double density /* = 10.0 */)
{
	//定义形状  多边形
	b2PolygonShape spriteShape;

	CCSize size = sprite->getContentSize();

	spriteShape.SetAsBox(size.width / PTM_RATIO / 2, size.height / PTM_RATIO / 2);

	//创建一个夹具的对像
	b2FixtureDef spriteShapeDef;

	//设置形状
	spriteShapeDef.shape = &spriteShape;

	//密度
	spriteShapeDef.density = density;

	spriteShapeDef.isSensor = true;

	b2Body *spriteBody = sprite->getB2Body();

	spriteBody->CreateFixture(&spriteShapeDef);
}

void Box2dHandler::addBodyForSprite(B2Sprite *sprite, double density /* = 10.0 */)
{
	b2BodyDef spriteBodyDef;

	//物体类型为动态物体
	spriteBodyDef.type = b2_dynamicBody;

	spriteBodyDef.position.Set(sprite->getPositionX() / PTM_RATIO, sprite->getPositionY() / PTM_RATIO);

	spriteBodyDef.userData = sprite;

	b2Body *spriteBody = m_world->CreateBody(&spriteBodyDef);

	sprite->setB2Body(spriteBody);

	this->addFixtureForSprite(sprite, density);
}

void Box2dHandler::update(float dt)
{
	int velocityIterations = 8;

	int positionIterations = 8;

	m_world->Step(dt, velocityIterations, positionIterations);

	for (b2Body *b = m_world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			CCSprite* myActor = (CCSprite*)b->GetUserData();
			myActor->setPosition(ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
		}
	}
}

void Box2dHandler::BeginConact(b2Contact *cantact)
{
	b2ContactListener::BeginContact(cantact);
	CCLog("开始碰撞");
}

void Box2dHandler::EndConact(b2Contact *cantact)
{
	b2ContactListener::EndContact(cantact);
	CCLog("结束碰撞");
}

void Box2dHandler::dealCollisions()
{

}