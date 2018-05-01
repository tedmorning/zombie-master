#include "cocos-ext.h"
#include "TString.h"
#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;
USING_NS_CC::ui;

#define FRAME 60

#define PI 3.1415926

#define PTM_RATIO 32.0

typedef long long int64;

//计算整型变量数字长度
short countIntNumber(int num);

//根据两点计算角度
float twoPoint(CCPoint point1, CCPoint point2);

//根据两点算出0~180度的角度
float twopointdegree(CCPoint point1,CCPoint point2);

//把字符串转换成整型
int stringChangeInt(string str);

//碰撞检测
bool isRectCollsion(int x, int y, int w, int h, int x1, int y1, int w1, int h1);

//设置是否启用控件(包括子控件,显示跟事件回调一起改变)的事件
void setEnableAll(Widget* root, bool enabled);

//设置是否显示和启用控件，（调用此方法显示与交互的状态同时改变）
void setVisibleAndEnable(UILayer* root, const char* name, bool visible);

//获取随机数(包括min  不包括max)
int getRandom(int min, int max);

//判断点在线的哪一边
//x1, y1, x2, y2, 线的上两点
//point_x, point_y 要判断的点
char coll(short x1, short y1, short x2, short y2, short point_x, short point_y);

//裁切图片
void clipImageView(UIImageView *img, CCRect &rect);

//是否移动到文件到缓存目录
bool checkCacheFile();

//移动文件到缓存目录中
bool moveFile(const char* filename);

//读数据
char* readTextFromFile(const char* filename);

//写数据
bool writeTextToFile(const char* filename, const char* data);

//读json文本
bool readJsonFromFile(const char* filename, rapidjson::Document& json);

//写json文本
bool writeJsonToFile(const char* filename, rapidjson::Document& json);

//设置控件可见跟交互
#define setVisible_Enable(ul_obj, widgetName, visible) setVisibleAndEnable(ul_obj, widgetName, visible);
//注册控件回调函数
#define registerTouchEvent(ul_obj, widgetName, targe, _SELECTOR) ul_obj->getWidgetByName(widgetName)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))

//获得按钮指针对象(UILayer*, tag|name)
#define buttonObj_tag(ul_obj, tag) dynamic_cast<UIButton*>(ul_obj->getWidgetByTag(tag))
#define buttonObj_name(ul_obj, btn_name) dynamic_cast<UIButton*>(ul_obj->getWidgetByName(btn_name))
//为按钮注册事件(UILayer*, tag, CCObject*, SEL_CancelEvent)
#define buttonTagCallback(ul_obj, tag, targe, _SELECTOR) buttonObj_tag(ul_obj, tag)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))
#define buttonNameCallback(ul_obj, btn_name, targe, _SELECTOR) buttonObj_name(ul_obj, btn_name)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))



//获得图片指针对象(UILayer*, tag|name)
#define imageObj_tag(ul_obj, tag) dynamic_cast<UIImageView*>(ul_obj->getWidgetByTag(tag))
#define imageObj_name(ul_obj, img_name) dynamic_cast<UIImageView*>(ul_obj->getWidgetByName(img_name))

//复选框事件
#define checkBoxObj_tag(ul_obj, tag) dynamic_cast<UICheckBox*>(ul_obj->getWidgetByTag(tag))
#define checkBoxObj_name(ul_obj, checkBox_name) dynamic_cast<UICheckBox*>(ul_obj->getWidgetByName(checkBox_name))
#define checkBoxTagCallback(ul_obj, tag, targe, _SELECTOR) checkBoxObj_tag(ul_obj, tag)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))
#define checkBoxNameCallback(ul_obj, checkBox_name, targe, _SELECTOR) checkBoxObj_name(ul_obj, checkBox_name)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))

//获得数字标签的指针对象
#define labelAtlasObj_tag(ul_obj, tag) dynamic_cast<UILabelAtlas*>(ul_obj->getWidgetByTag(tag))
#define labelAtlasObj_name(ul_obj, label_name) dynamic_cast<UILabelAtlas*>(ul_obj->getWidgetByName(label_name))

// loading bar
#define loadingBarObj_tag(ul_obj, tag) dynamic_cast<UILoadingBar*>(ul_obj->getWidgetByTag(tag))
#define loadingBarObj_name(ul_obj, label_name) dynamic_cast<UILoadingBar*>(ul_obj->getWidgetByName(label_name))

//获得标签的指针对像
#define labelObj_tag(ul_obj, tag) dynamic_cast<UILabel*>(ul_obj->getWidgetByTag(tag))
#define labelObj_name(ul_obj, label_name) dynamic_cast<UILabel*>(ul_obj->getWidgetByName(label_name))

//获得容器(Panel)的指针对象
#define panelObj_tag(ul_obj, tag) dynamic_cast<UIPanel*>(ul_obj->getWidgetByTag(tag))
#define panelObj_name(ul_obj, panel_name) dynamic_cast<UIPanel*>(ul_obj->getWidgetByName(panel_name))
#define panelTagCallback(ul_obj, tag, targe, _SELECTOR) panelObj_tag(ul_obj, tag)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))
#define panelNameCallback(ul_obj, panel_name, targe, _SELECTOR) panelObj_name(ul_obj, panel_name)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))



void moveIn(CCNode * node);