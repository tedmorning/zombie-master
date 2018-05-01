#pragma once
#include <string>
using namespace std;


class TString : public std::string
{
public:
	TString(void);
	TString(const char *_Ptr);
	~TString(void);
	

	TString& operator+=(int num);

	TString& operator+=(float num);

	TString& operator+=(const char *_Ptr);
private:
	//string str;
};