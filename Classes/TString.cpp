#include "TString.h"

TString::TString()
{

}

TString::TString(const char *_Ptr) : basic_string(_Ptr)
{
	
}

TString::~TString()
{

}

TString& TString::operator+=(int num)
{
	int length = 0;//记录num有多少位
	int divr = 0; //除数
	bool temp = false;
	while(this)
	{
		if(num >= divr)
		{
			length ++;
		}
		else 
		{
			break;
		}
		if(!temp)
		{
			divr = 10;
			temp = true;
		}
		else 
		{
			divr *= 10;
		}
	}
	char ss[5];
	int temp2 = divr/10;
	int temp3 = num;
	for (int i=0; i<length; ++i)
	{
		ss[i] = temp3/temp2 + 48;
		temp3 %= temp2;
		temp2 /= 10;
	}
	ss[length] = '\0';
	append(ss);
	return (*this);
}

TString& TString::operator+=(float num)
{
	return (*this);
}

TString& TString::operator+=(const char *_Ptr)
{
	append(_Ptr);
	return (*this);
}