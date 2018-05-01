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

//�������ͱ������ֳ���
short countIntNumber(int num);

//�����������Ƕ�
float twoPoint(CCPoint point1, CCPoint point2);

//�����������0~180�ȵĽǶ�
float twopointdegree(CCPoint point1,CCPoint point2);

//���ַ���ת��������
int stringChangeInt(string str);

//��ײ���
bool isRectCollsion(int x, int y, int w, int h, int x1, int y1, int w1, int h1);

//�����Ƿ����ÿؼ�(�����ӿؼ�,��ʾ���¼��ص�һ��ı�)���¼�
void setEnableAll(Widget* root, bool enabled);

//�����Ƿ���ʾ�����ÿؼ��������ô˷�����ʾ�뽻����״̬ͬʱ�ı䣩
void setVisibleAndEnable(UILayer* root, const char* name, bool visible);

//��ȡ�����(����min  ������max)
int getRandom(int min, int max);

//�жϵ����ߵ���һ��
//x1, y1, x2, y2, �ߵ�������
//point_x, point_y Ҫ�жϵĵ�
char coll(short x1, short y1, short x2, short y2, short point_x, short point_y);

//����ͼƬ
void clipImageView(UIImageView *img, CCRect &rect);

//�Ƿ��ƶ����ļ�������Ŀ¼
bool checkCacheFile();

//�ƶ��ļ�������Ŀ¼��
bool moveFile(const char* filename);

//������
char* readTextFromFile(const char* filename);

//д����
bool writeTextToFile(const char* filename, const char* data);

//��json�ı�
bool readJsonFromFile(const char* filename, rapidjson::Document& json);

//дjson�ı�
bool writeJsonToFile(const char* filename, rapidjson::Document& json);

//���ÿؼ��ɼ�������
#define setVisible_Enable(ul_obj, widgetName, visible) setVisibleAndEnable(ul_obj, widgetName, visible);
//ע��ؼ��ص�����
#define registerTouchEvent(ul_obj, widgetName, targe, _SELECTOR) ul_obj->getWidgetByName(widgetName)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))

//��ð�ťָ�����(UILayer*, tag|name)
#define buttonObj_tag(ul_obj, tag) dynamic_cast<UIButton*>(ul_obj->getWidgetByTag(tag))
#define buttonObj_name(ul_obj, btn_name) dynamic_cast<UIButton*>(ul_obj->getWidgetByName(btn_name))
//Ϊ��ťע���¼�(UILayer*, tag, CCObject*, SEL_CancelEvent)
#define buttonTagCallback(ul_obj, tag, targe, _SELECTOR) buttonObj_tag(ul_obj, tag)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))
#define buttonNameCallback(ul_obj, btn_name, targe, _SELECTOR) buttonObj_name(ul_obj, btn_name)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))



//���ͼƬָ�����(UILayer*, tag|name)
#define imageObj_tag(ul_obj, tag) dynamic_cast<UIImageView*>(ul_obj->getWidgetByTag(tag))
#define imageObj_name(ul_obj, img_name) dynamic_cast<UIImageView*>(ul_obj->getWidgetByName(img_name))

//��ѡ���¼�
#define checkBoxObj_tag(ul_obj, tag) dynamic_cast<UICheckBox*>(ul_obj->getWidgetByTag(tag))
#define checkBoxObj_name(ul_obj, checkBox_name) dynamic_cast<UICheckBox*>(ul_obj->getWidgetByName(checkBox_name))
#define checkBoxTagCallback(ul_obj, tag, targe, _SELECTOR) checkBoxObj_tag(ul_obj, tag)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))
#define checkBoxNameCallback(ul_obj, checkBox_name, targe, _SELECTOR) checkBoxObj_name(ul_obj, checkBox_name)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))

//������ֱ�ǩ��ָ�����
#define labelAtlasObj_tag(ul_obj, tag) dynamic_cast<UILabelAtlas*>(ul_obj->getWidgetByTag(tag))
#define labelAtlasObj_name(ul_obj, label_name) dynamic_cast<UILabelAtlas*>(ul_obj->getWidgetByName(label_name))

// loading bar
#define loadingBarObj_tag(ul_obj, tag) dynamic_cast<UILoadingBar*>(ul_obj->getWidgetByTag(tag))
#define loadingBarObj_name(ul_obj, label_name) dynamic_cast<UILoadingBar*>(ul_obj->getWidgetByName(label_name))

//��ñ�ǩ��ָ�����
#define labelObj_tag(ul_obj, tag) dynamic_cast<UILabel*>(ul_obj->getWidgetByTag(tag))
#define labelObj_name(ul_obj, label_name) dynamic_cast<UILabel*>(ul_obj->getWidgetByName(label_name))

//�������(Panel)��ָ�����
#define panelObj_tag(ul_obj, tag) dynamic_cast<UIPanel*>(ul_obj->getWidgetByTag(tag))
#define panelObj_name(ul_obj, panel_name) dynamic_cast<UIPanel*>(ul_obj->getWidgetByName(panel_name))
#define panelTagCallback(ul_obj, tag, targe, _SELECTOR) panelObj_tag(ul_obj, tag)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))
#define panelNameCallback(ul_obj, panel_name, targe, _SELECTOR) panelObj_name(ul_obj, panel_name)->addTouchEventListener(targe, SEL_TouchEvent(&_SELECTOR))



void moveIn(CCNode * node);