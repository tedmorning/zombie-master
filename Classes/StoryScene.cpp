#include "StoryScene.h"
#include "ZombieSound.h"
#include "tool.h"
#include "ChoosePerson.h"
#include "CCShake.h"
#include "JniCommon.h"
#include "data_center//RunningData.h"
CCScene* StoryScene::scene(int story, bool isSkip)
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	StoryScene *layer = StoryScene::create(story, isSkip);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

StoryScene* StoryScene::create(int story, bool isSkip)
{
	StoryScene *pRet = new StoryScene();
	pRet->curStoryIndex = story;
	pRet->isSkip = isSkip;

	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}

}
enum ButtonTag 
{
	ButtonTag_Skip = 4603,
	ButtonTag_Skip_2 = 4636,
	ButtonTag_Skip_3 = 4669
};


bool StoryScene::init()
{
	if (!CCLayer::init())
		return false;

	moveIn(this);
	if (curStoryIndex == k_story_one)
	{
		ui_1 = TouchGroup::create();
		ui_1->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/Story_1.ExportJson"));

// 		UIImageView*  pImageView = imageObj_name(ui_1, "Image_1");
// 		pImageView->loadTexture("story_page_one.jpg", UI_TEX_TYPE_LOCAL);
		
// 		UIImageView* pChatThree = imageObj_name(ui_1, "chat_3");
// 		pChatThree ->setVisible(true);

		fontCount = 0;
		m_chatLineCount = 3;
	} else if(curStoryIndex == k_story_two)
	{
		ui_1 = TouchGroup::create();
		ui_1->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/Story_2.ExportJson"));
		m_chatLineCount = 2;
// 
// 		for(int i=1; i<=6; i++)
// 		{
// 			UIImageView* pImageView = imageObj_tag(ui_1, 4620+i);
// 			pImageView->setVisible(false);
// 		}
		UIImageView* pChatThree = imageObj_name(ui_1, "chat_1");
		pChatThree->setVisible(true);


		UIImageView* pChat = imageObj_name(ui_1, "chat_2");
		pChat->setVisible(true);

		fontCount = 34;


	}else if(curStoryIndex == k_story_three)
	{
		ui_1 = TouchGroup::create();
		ui_1->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/Story_3.ExportJson"));
		m_chatLineCount = 2;

// 		UIImageView* pImageViewOne = imageObj_name(ui_1, "role_1");
// 		pImageViewOne->setVisible(false);
// 		
// 		UIImageView* pImageViewTwo = imageObj_name(ui_1, "role_2");
// 		pImageViewTwo->setVisible(false);
// 
// 		UIImageView* pImageViewThree = imageObj_name(ui_1, "role_3");
// 		pImageViewThree->setVisible(false);

		UIButton * close = buttonObj_name(ui_1, "close");
		close->addTouchEventListener(this,SEL_TouchEvent(&StoryScene::onClose));
		fontCount = 61;
	}

	addChild(ui_1, 2);

	registerTouchEvent(ui_1, "skip", this, StoryScene::buttonClicked);

// 	UIImageView* pChatOne = imageObj_name(ui_1,"chat_1");
// 	UIImageView* pChatTwo = imageObj_name(ui_1, "chat_2");



	appearPercent = 0;
	appearPercentCount =0;
	waitCount = 0;
	nextLine = 0;
	fontOffset = 0;
	firstShen = true;

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("story_chat.plist");

	initStoryInfo(); //初始化故事信息
	
	storyBegin();

	return true;
}

void StoryScene::initStoryInfo()
{
	storyInfo.lineInfos.reserve(5);

	for(int j=0; j<m_chatLineCount; j++)
	{
		LineInfo li;
		li.index = j+1;
		
		storyInfo.lineInfos.push_back(li);
	}
}

void StoryScene::storyBegin()
{
	return;
	curLineIndex = 0;
	CCBlink* pBlink = CCBlink::create(1,3);
	CCRepeatForever* pRepeatForever = CCRepeatForever::create(pBlink);
	
	pCursor = imageObj_name(ui_1, "cursor");
	cursorBeginX = pCursor->getPositionX();

	pCursor->runAction(pRepeatForever);
	
	if (curStoryIndex == k_story_one)
	{
		schedule(schedule_selector(StoryScene::setFontPercent),0.12);
		//schedule(schedule_selector(StoryScene::bgMove));
	} else if(curStoryIndex == k_story_two)
	{
		if(isSkip)
		{
			scheduleOnce(schedule_selector(StoryScene::storytwo),0.5);
		} else 
		{
			scheduleOnce(schedule_selector(StoryScene::storytwo), 1.5);
		}
	
		
	} else if(curStoryIndex == k_story_three)
	{
		if(isSkip)
		{
			scheduleOnce(schedule_selector(StoryScene::storythreeBegin), 0.5);
		} else 
		{
			scheduleOnce(schedule_selector(StoryScene::storythreeBegin), 1.8);
		}
	}

}


void StoryScene::goNextLine(float dt)
{
	vector<LineInfo> lineInfos = storyInfo.lineInfos;

	char tem[10];
	sprintf(tem, "chat_%i", lineInfos.at(curLineIndex).index);

	UIImageView* pImageView = imageObj_name(ui_1,tem);
	pCursor->setPosition(ccp(cursorBeginX,  pImageView->getPositionY()));

	if(curStoryIndex == 0)
	{
		if(curLineIndex == 1 || curLineIndex == 2)
		{
			schedule(schedule_selector(StoryScene::setFontPercent),0.12);
		} else
		{
			schedule(schedule_selector(StoryScene::setFontPercent),0.09);
		}
	} else if(curStoryIndex == 1)
	{
		schedule(schedule_selector(StoryScene::setFontPercent),0.09);

	} else if(curStoryIndex == 2)
	{
		schedule(schedule_selector(StoryScene::setFontPercent),0.09);
	}
	
}


void StoryScene::fontWait(float dt)
{
	schedule(schedule_selector(StoryScene::setFontPercent),0.12);
}


void StoryScene::storytwo(float dt)
{
	aearCount = 0;
	schedule(schedule_selector(StoryScene::bgShow),0.7);
	schedule(schedule_selector(StoryScene::setFontPercent),0.1);
}

void StoryScene::storythreeBegin(float dt)
{
	roleCount = 0;
	schedule(schedule_selector(StoryScene::setFontPercent),0.15);
}

void StoryScene::storythreeEnd(float dt)
{
	scheduleOnce(schedule_selector(StoryScene::nextStory),0.8);
}

void StoryScene::appearFont()
{
	schedule(schedule_selector(StoryScene::setFontPercent),0.15);
}

void StoryScene::setFontPercent(float dt)
{
	//waitCount++;
	//if(waitCount<5) return;

		char tem[30];
		fontCount++;

		/*因图片名不同，特殊处理*/
		if(fontCount == 1 || fontCount == 2)
		{
			sprintf(tem, "story_chat_1_%i.png", fontCount);
		}  else 
		{
			sprintf(tem, "%i.png", fontCount);
		}

		CCSprite* pFont = NULL;
		if(fontCount == 18 && firstShen)
		{
			pFont = CCSprite::createWithSpriteFrameName("story_chat_shen.png");
		} else 
		{				
			pFont = CCSprite::createWithSpriteFrameName(tem);
		}

		//得到文字间距
		if(fontCount == 1 || fontCount == 35 || fontCount == 62 || fontCount== 44
			|| fontCount == 11 || fontCount==62 || fontCount == 67 || fontCount == 18)
		{
			fontOffset =0;
		} else 
		{
			CCNode* pNode = getChildByTag(fontCount-1);
			fontOffset = pNode->getContentSize().width*0.1;
		}

		/*因图片名不同，特殊处理*/
		if(fontCount == 18 && !firstShen)
		{
			fontOffset += 5;
		}

		CCPoint point = pCursor->getPosition();
		pFont->setPosition(ccp(point.x + fontOffset, point.y));
		pFont->setAnchorPoint(ccp(0,0));
		addChild(pFont,1000, fontCount);

		float pX = pCursor->getPositionX();
		pCursor->setPositionX(pX+fontOffset+25);

		/*逗号停顿*/
		if(fontCount == 25 || fontCount == 54 /*|| fontCount == 68*/ || fontCount == 77)
		{
			unschedule(schedule_selector(StoryScene::setFontPercent));
			scheduleOnce(schedule_selector(StoryScene::fontWait),0.8);
		}

		/* 下一行 */
		if(fontCount == 10 || fontCount == 17 || fontCount==34
			|| fontCount== 43 || fontCount==61
			|| fontCount== 66 || fontCount== 84)
		{
			nextLine++;
			unschedule(schedule_selector(StoryScene::setFontPercent));
			nextLine = 0;
			appearPercent = 0;

			//是最后一行则退出
			curLineIndex++;
			vector<LineInfo> lineInfos = storyInfo.lineInfos;
			if(lineInfos.size() == curLineIndex) 
			{
				unschedule(schedule_selector(StoryScene::setFontPercent));

				if(curStoryIndex == 2)
				{
					schedule(schedule_selector(StoryScene::roleShow),0.4);
				}
				return;
			}

			if(fontCount== 43) //故事二，不停顿
			{
				goNextLine(true);
			} else if(curStoryIndex == 2)
			{
				scheduleOnce(schedule_selector(StoryScene::goNextLine),1.5);
			} else 
			{
				scheduleOnce(schedule_selector(StoryScene::goNextLine),0.5);
			}
			
		}

		/*因图片名不同，特殊处理*/
		if(fontCount == 18 && firstShen)
		{
			firstShen= false;
			fontCount--;
		}
}

void StoryScene::bgMove(float dt)
{

	return;
	UIImageView*  pImageView = imageObj_name(ui_1, "Image_1");
	
	float y = pImageView->getPositionY();
	if(y>0)
	{
		unschedule(schedule_selector(StoryScene::bgMove));
		scheduleOnce(schedule_selector(StoryScene::nextStory),0.45);

	} else 
	{
		pImageView->setPositionY(y+1.8);
	}
}

void StoryScene::bgShow(float dt)
{
	aearCount++;
	if(aearCount == 6)
	{
		unschedule(schedule_selector(StoryScene::bgShow));
		scheduleOnce(schedule_selector(StoryScene::nextStory),0.3);
	}
	UIImageView* pImageView = imageObj_tag(ui_1, 4620+aearCount);
	pImageView->setVisible(true);
}

void StoryScene::roleShow(float dt)
{
	roleCount++;
	if(roleCount>3) 
	{
		scheduleOnce(schedule_selector(StoryScene::storythreeEnd),0.1);
		return;
	}

	
	char tem[20];

	sprintf(tem, "role_%i", roleCount);

	UIImageView* pImageViewOne = imageObj_name(ui_1, tem);
	
	sprintf(tem, "story_3_%i.png", roleCount);

	CCSprite* pSprite = CCSprite::createWithSpriteFrameName(tem);
	pSprite->setPosition(pImageViewOne->getPosition());
    //	CCActionInterval*  action1 = CCFadeIn::create(0.5f);
	//	pSprite->setOpacity(0);

	if(roleCount == 3)
	{
		CCActionInterval*  action1 =CCShake::create(0.2,20);
		pSprite->runAction(action1);
		addChild(pSprite,2);
	} else 
	{
		CCActionInterval*  action1 =CCShake::create(0.1,10);
		pSprite->runAction(action1);
		addChild(pSprite,2);
	}

	
}

void StoryScene::nextStory(float dt)
{

	if(curStoryIndex == k_story_end-1)
	{
		CCDirector::sharedDirector()->replaceScene(ChoosePerson::scene());
		return;
	}
	CCDirector::sharedDirector()->replaceScene(StoryScene::scene(curStoryIndex + 1, false));

//	CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(3, StoryScene::scene(curStoryIndex+1, false)));

}

void StoryScene::buttonClicked(CCObject *pSender, TouchEventType eType)
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
	case ButtonTag_Skip:
		{
			stopAllActions();

			CCDirector::sharedDirector()->replaceScene(StoryScene::scene(curStoryIndex + 1, true));
			//CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1, StoryScene::scene(curStoryIndex+1, true)));
		}
		break;
	case ButtonTag_Skip_2:
		{
			stopAllActions();
			CCDirector::sharedDirector()->replaceScene(StoryScene::scene(curStoryIndex + 1, true));
			//CCDirector::sharedDirector()->replaceScene( CCTransitionFade::create(1, StoryScene::scene(curStoryIndex+1, true)));
		}
		break;
	case ButtonTag_Skip_3:
		{
			//CCDirector::sharedDirector()->replaceScene(ChoosePerson::scene());
			//CCLOG("skip") ;
			payCode(k_pay_story, this, Sel_Pay_Event(&StoryScene::payCallBack));
	
		}
		
		break;

	default:
		break;
	}
	
}

void StoryScene::payCallBack(bool res)
{
	if (res)
	{
		Resource& resource = RunningData::getInstance()->getResource();
		resource.addShield(2);
		resource.addUniqueKill(2);
		resource.addGold(20000);
		CCDirector::sharedDirector()->replaceScene(ChoosePerson::scene());
	}
}

void StoryScene::onClose(CCObject *pSender, TouchEventType eType)
{
	if (eType == TOUCH_EVENT_BEGAN)
	{
		CCDirector::sharedDirector()->replaceScene(ChoosePerson::scene());
	}
}
