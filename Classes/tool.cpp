#include "tool.h"
#include "support/data_support/ccCArray.h"
#include "math.h"
#include "CocoStudio\Json\rapidjson\stringbuffer.h"
#include "CocoStudio\Json\rapidjson\writer.h"


short countIntNumber(int num)
{
	short count = 1;
	while (true)
	{
		num /= 10;
		if (num == 0)
		{
			break;
		}
		count++;
	}
	return count;
}

int stringChangeInt(string str)
{
	int num = 0;
	int id = 1;
	//判断是否正数
	bool plus = true;
	for (unsigned short i = 0; i < str.size(); ++i)
	{
		if (str[i] == '-')
		{
			plus = false;
			continue;
		}
		num = num * 10 + (str[i]-48);
	}
	if (!plus)
	{
		num *= -1;
	}
	return num;
}

bool isRectCollsion(int x, int y, int w, int h, int x1, int y1, int w1, int h1)
{
	if(x > x1+w1 || x+w < x1 || y > y1+h1 || y+h < y1){
		return false;
	}
	return true;
}

int getRandom(int min, int max)
{
	return rand() % (max-min) + min;
}

//判断点在线的哪一边
char coll(short x1, short y1, short x2, short y2, short point_x, short point_y)
{
	int a = y2 - y1;
	int b = x1 - x2;
	int c = x2*y1 - x1*y2;
	int te = a*point_x + b*point_y + c;
	if (te == 0)
	{
		return 0;
	}
	else if(te < 0) //在线左边
	{
		return 1;
	}
	else //在线右边
	{
		return 2;
	}
}

void setEnableAll(Widget* root, bool enabled)
{
	if (!root)
	{
		return;
	}
	ccArray* arrayRootChildren = root->getChildren()->data;
	int length = arrayRootChildren->num;
	if(length == 0)
	{
		root->setEnabled(enabled);
		return;
	}
	else 
	{
		for (int i=0;i<length;i++)
		{
			setEnableAll(static_cast<Widget*>(arrayRootChildren->arr[i]), enabled);
		}
	}
}

void setVisibleAndEnable(UILayer* root, const char* name, bool visible)
{
	root->getWidgetByName(name)->setVisible(visible);
	root->getWidgetByName(name)->setEnabled(visible);
}

void clipImageView(UIImageView *img, CCRect &rect)
{
	CCSprite * sp = static_cast<CCSprite*>(img->getVirtualRenderer());
	CCRect re = sp->getTextureRect();
	re.origin.x += rect.origin.x;
	re.origin.y += rect.origin.y;
	re.size = rect.size;
	sp->setTextureRect(re);
}

float twoPoint(CCPoint point1, CCPoint point2)
{
	float scale = 0;
	float an = 0;
	if (point2.x > point1.x)
	{
		scale = fabs(point2.x - point1.x) / fabs(point2.y - point1.y);
		an = atan(scale);
		if (point2.y < point1.y)
		{
			an = (180 - an / PI * 180) * PI / 180;
		}
	}
	else
	{
		scale = fabs(point1.x - point2.x) / fabs(point1.y - point2.y);
		an = atan(scale);
		if (point2.y < point1.y)
		{
			
			an = (an / PI * 180 + 180) * PI / 180;
		}
		else
		{
			an = (360 - an / PI * 180) * PI / 180;
		}
	}
	return an;
}

float twopointdegree(CCPoint point1,CCPoint point2)
{
	// point1 为起始点
	float scale = 0;
	float an = 0;
	if (point2.x > point1.x)
	{
		scale = fabs(point2.x - point1.x) / fabs(point2.y - point1.y);
		an = atan(scale);
		an = an / PI * 180 + 90;
	}
	else
	{
		scale = fabs(point1.x - point2.x) / fabs(point1.y - point2.y);
		an = atan(scale);
		an = 90 - an / PI * 180;
	}
	return an;
}

bool checkCacheFile()
{
	bool bRet = true;

	string finalPath = CCFileUtils::sharedFileUtils()->getWritablePath() + "tag.b";
	unsigned long  size = 0;
	unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(finalPath.c_str(), "rb+", &size);
	if(!data)
	{
		FILE* fp = fopen(finalPath.c_str(), "wb+");
		string new_data("1");
		if(fp)
		{
			fputs(new_data.c_str(), fp);
			fclose(fp);
		}

		bRet = false;
	}

	return bRet;
}

bool moveFile(const char* filename)
{
	bool bRet = true;
	string finalPath = "data/";
	finalPath += filename;
	finalPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(finalPath.c_str());
	unsigned long  size = 0;
	unsigned char* data = CCFileUtils::sharedFileUtils()->getFileData(finalPath.c_str(), "rb+", &size);
	if(!data)
	{
		std::string msg = "Get data from file(";
		msg.append(finalPath).append(") failed!");

		CCLOG("%s", msg.c_str());

		bRet = false;
	}

	char* cpy_data = new char[size + 2];
	cpy_data[size + 0] = 0;
	cpy_data[size + 1] = 0;
	memcpy(cpy_data, data, size);

	delete[] data;

	finalPath = CCFileUtils::sharedFileUtils()->getWritablePath() + filename;
	FILE* fp = fopen(finalPath.c_str(), "wb+");
	
	if(fp)
	{
		fputs(cpy_data, fp);
		fclose(fp);
	}

	delete[] cpy_data;

	return bRet;
}

char* readTextFromFile(const char* filename)
{
	CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();

	string finalPath = CCFileUtils::sharedFileUtils()->getWritablePath() + filename;
	unsigned long  size = 0;
	unsigned char* data = fileUtils->getFileData(finalPath.c_str(), "rb+", &size);
	if (!data)
	{
		std::string msg = "Get data from file(";
		msg.append(finalPath).append(") failed!");

		CCLOG("%s", msg.c_str());

		return NULL;
		
	}

	char* cpy_data = new char[size + 2];
	cpy_data[size + 0] = 0;
	cpy_data[size + 1] = 0;
	memcpy(cpy_data, data, size);

	delete[] data;

	return cpy_data;
}

bool writeTextToFile(const char* path, const char* data)
{

	//CCLOG("%s ",data);

	bool bRet = false;

	string finalPath = CCFileUtils::sharedFileUtils()->getWritablePath() + path;
	FILE* fp = fopen(finalPath.c_str(), "wb+");
	
	if(fp)
	{
		fputs(data, fp);
		fclose(fp);
		bRet = true;
	}
		
	return bRet;
}


bool  readJsonFromFile(const char* path, rapidjson::Document& json)
{
	char* txt_s = readTextFromFile(path);
	if (txt_s == NULL)
		return false;

	json.Parse<0>(txt_s);
	
	bool ret = true;
	if (json.HasParseError()) {
        CCLOG("ReadJsonFromFile %s\n",json.GetParseError());
		ret = false;
    }
	delete[] txt_s;

	return ret;
}

bool writeJsonToFile(const char* path, rapidjson::Document& json)
{

	rapidjson::StringBuffer  buffser;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffser);
    json.Accept(writer);
	
	::writeTextToFile(path, buffser.GetString());

	return true;
}

void moveIn(CCNode * node)
{
	node->setPosition(ccp(800,0));
	node->runAction(CCMoveTo::create(0.5,ccp(0,0)));
}
