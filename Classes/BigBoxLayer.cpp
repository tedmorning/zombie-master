#include "BigBoxLayer.h"

#include "tool.h"
BigBoxLayer::BigBoxLayer()
{
	
}


BigBoxLayer::~BigBoxLayer()
{
}

bool BigBoxLayer::init()
{
	moveIn(this);
	CCLayer::init();
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCMenuItemImage * box = CCMenuItemImage::create("gifbuttton.png", "gifbuttton.png", this, menu_selector(BigBoxLayer::onClick));
	box->setPosition(ccp(size.width/2,size.height/2));
	CCMenu * menu = CCMenu::create(box,nullptr);
	addChild(menu);
	menu->setPosition(ccp(0,0));
	return true;
}

void BigBoxLayer::onClick(CCObject * obj)
{
	if (m_callFun)
		m_callFun();
}

void BigBoxLayer::setCallFun(std::function<void()> callFun)
{
	m_callFun = callFun;
}


