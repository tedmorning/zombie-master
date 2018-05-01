#include "PromptBox.h"
#include "tool.h"
#include "ZombieSound.h"

enum ButtonTag 
{
	ButtonTag_Cancel = 4584,
	ButtonTag_Confirm, 
};

bool PromptBox::init()
{
	if (!CCLayer::init())
		return false;

	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//当前层的位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCLayerColor* layercolor = CCLayerColor::create(ccc4(0,0,0,150),800,480) ;
	addChild(layercolor) ;

	ui = TouchGroup::create();
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/promptBox.ExportJson"));

	ui->setScale(0.8);
	addChild(ui, 2);

	registerTouchEvent(ui, "prompt_cancel", this, PromptBox::buttonClicked);
	registerTouchEvent(ui, "prompt_confirm", this, PromptBox::buttonClicked);

	return true;
}

void PromptBox::buttonClicked(CCObject *pSender, TouchEventType eType)
{

	if (eType != TOUCH_EVENT_ENDED)
	{
		return;
	}
	
	::playSound("music/click.ogg");

	UIButton *button = dynamic_cast<UIButton*>(pSender) ;
	int tag = button->getTag() ;

	switch (tag)
	{
	case ButtonTag_Cancel:
		{
			removeFromParent();
		}
		
		break;
	case ButtonTag_Confirm:
		{
			CCDirector::sharedDirector()->end();
		}
		break;

	default:
		break;
	}
	
}
