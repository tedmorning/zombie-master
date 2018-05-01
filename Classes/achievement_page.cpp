#include "achievement_page.h"
#include "tool.h"
#include "ZombieSound.h"
#include "GameMainMenu.h"
#include "data_center\RunningData.h"
#include "CocoStudio\GUI\UIWidgets\UIImageView.h"

enum ButtonTag 
{
	ButtonTagBackToMain = 5103, 
	ButtonTagSure = 33   
};
CCScene* AchievementPage::scene()
{
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	AchievementPage *layer = AchievementPage::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool AchievementPage::init()
{
	if (!CCLayer::init())
		return false;

	//窗口大小
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//当前层的位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	ui = TouchGroup::create();
	ui->addWidget(GUIReader::shareReader()->widgetFromJsonFile("UI/GameMainMenu_1/achievement.ExportJson"));

	addChild(ui, 2);
  
	registerTouchEvent(ui, "Button_13", this, AchievementPage::buttonClicked) ;
//	registerTouchEvent(ui, "sure", this, ChoosePerson::buttonClicked) ;	

	int gold = RunningData::getInstance()->getResource().getGold();
	int killedNum = RunningData::getInstance()->getAchievement().getKilledZombieNumber();

	UILabelAtlas* pLableGold = labelAtlasObj_name(ui, "AtlasLabel_38");
	UILabelAtlas* pLableKilledNum = labelAtlasObj_name(ui, "AtlasLabel_37");

	char tem[80];
	sprintf(tem,"%i", gold);
	pLableGold->setStringValue(tem);

	sprintf(tem,"%i", killedNum);
	pLableKilledNum->setStringValue(tem);

	 UIScrollView *pScrollView = dynamic_cast<UIScrollView*>(ui->getWidgetByName("ScrollView_25"));

	 UIImageView* pImageOne = imageObj_name(ui, "Image_50");
	 pImageOne->setPositionY(pImageOne->getPositionY());
	 pImageOne->setVisible(false);

     //确定出scrollview的滚动那个区域的size
     int iheight = 0;

     iheight = pImageOne->getContentSize().height;
     pScrollView->setInnerContainerSize(CCSizeMake(pScrollView->getInnerContainerSize().width,11*iheight));
     pScrollView->setBounceEnabled(true);//设置scrollview的回弹效果

    //向scrollview中添加控件
	 Achievement& achi = RunningData::getInstance()->getAchievement();
	 int length = 11;
     for(int i=0;i<length;i++)
     {   
         UIImageView *pImageBg = UIImageView::create();
		 if(achi.achievements[i].done == 0)
		 {
			 pImageBg->loadTexture("achievement_none.png",UI_TEX_TYPE_PLIST);
		 } else 
		 {
			pImageBg->loadTexture("achievement_done.png",UI_TEX_TYPE_PLIST);
		 }
		 pImageBg->setPosition(ccp(pImageOne->getPositionX(),pImageOne->getPositionY() + iheight*(length-i-1)));
         pScrollView->addChild(pImageBg);

		 UIImageView *pImageFont = UIImageView::create();
		 sprintf(tem,"a%i.png", i + 1);
		 pImageFont->loadTexture(tem, UI_TEX_TYPE_PLIST);
		 pImageFont->setAnchorPoint(ccp(0,0));
		 pImageFont->setPosition(ccp(-120,-pImageFont->getContentSize().height*0.5));
		 pImageBg->addChild(pImageFont);
     }
    
	
	 //pScrollView->scrollToPercentVertical(50,1,true);
	 UISlider *pSlider = dynamic_cast<UISlider*>(ui->getWidgetByName("Slider_27"));
	 pSlider->addEventListenerSlider(this, sliderpercentchangedselector(AchievementPage::sliderEvent));

	 pScrollView->addEventListenerScrollView(this, scrollvieweventselector(AchievementPage::scrollEvent));
	return true;
}

void AchievementPage::scrollEvent(cocos2d::CCObject *pSender, ScrollviewEventType type)
{
    switch (type)
    {
        case SCROLLVIEW_EVENT_SCROLLING:
			{
				UIScrollView *pScrollView = dynamic_cast<UIScrollView*>(ui->getWidgetByName("ScrollView_25"));
				 UISlider *pSlider = dynamic_cast<UISlider*>(ui->getWidgetByName("Slider_27"));

				CCSize size = pScrollView->getContentSize();
				float csize = pScrollView->getInnerContainerSize().height;
				float minY = size.height - pScrollView->getInnerContainerSize().height;
			    float h = - minY;
				//pScrollView->getp
				//minY + percent * h / 100.0f
				float percent = (pScrollView->getInnerContainer()->getPositionY() - minY)*100/h;
				//CCLOG("SCROLL y:%f",percent);

				if(percent<0)
				{
					percent = 0;
				} else if(percent>100) 
				{
					percent = 100;
				}
				pSlider->setPercent(percent);
			}
            break;
            
        default:
            break;
    }
}
void AchievementPage::sliderEvent(CCObject *pSender, SliderEventType type)
{
    switch (type)
    {
        case SLIDER_PERCENTCHANGED:
        {
			 UIScrollView *pScrollView = dynamic_cast<UIScrollView*>(ui->getWidgetByName("ScrollView_25"));
            UISlider* slider = dynamic_cast<UISlider*>(pSender);
            int percent = slider->getPercent();
            pScrollView->scrollToPercentVertical(percent,1,true);
        }
            break;
            
        default:
            break;
    }
}

void AchievementPage::buttonClicked(CCObject *pSender, TouchEventType eType)
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
	case ButtonTagBackToMain:
		{
			CCLOG("backTomain") ;
			CCDirector::sharedDirector()->replaceScene(GameMainMenu::scene(false));
		}

		break;
	case ButtonTagSure:
		{

			//CCDirector::sharedDirector()->pushScene(CCTransitionFlipX::create(1.0f, LevelInstruction::scene()));
			//CCDirector::sharedDirector()->pushScene(CCTransitionFlipX::create(1.0f, BattleManage::scene()));

			CCLOG("sure!") ;
		}

		break;

	default:
		break;
	}
	
}

	