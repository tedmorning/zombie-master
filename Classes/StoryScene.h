#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;

enum StoryType
{
	k_story_one = 0,
	k_story_two,
	k_story_three,
	k_story_end
};

struct LineInfo
{
	int index;

};

struct StoryInfo
{
	std::vector<LineInfo> lineInfos;

};


class StoryScene :
	public cocos2d::CCLayer
{
public:
	virtual bool init();

	static CCScene* scene(int story, bool isSkip);

	void buttonClicked(CCObject *pSender, TouchEventType eType);

	static StoryScene* create(int story, bool isSkip);

	void payCallBack(bool res);
	void onClose(CCObject *pSender, TouchEventType eType);

private:

	void setFontPercent(float dt);
	void bgMove(float dt);
	void bgShow(float dt);
	void roleShow(float dt);
	void appearFont();
	void initStoryInfo();

	void nextStory(float dt);
    void goNextLine(float dt);
	void fontWait(float dt);
	void storyBegin();
	void storytwo(float dt);
	void storythreeEnd(float dt);
	void storythreeBegin(float dt);

	int appearPercent;
	int appearPercentCount;
	int waitCount;
	int nextLine;

	float fontMoveDuring;
	float fontOffset;
	float cursorMoveDuring;
	float cursorBeginX;

	CCNode* m_OneStory;
	UILoadingBar* pCurFontBar;
	UIImageView* pCursor;
	UIPanel* pPanel;


	CCPoint targetPoint;
	CCSprite* m_pFontSprite;
	CCSprite* m_promptSprite;

	TouchGroup* ui_1;
	TouchGroup* ui_2;
	TouchGroup* ui_3;

	StoryInfo storyInfo;
	int curStoryIndex;
	int curLineIndex;
	int isSkip;

	int aearCount;
	int roleCount;
	int fontCount;
	int m_chatLineCount;

	bool firstShen;
};
