#pragma once
#include"cocos2d.h"
class Utils
{
public:
	Utils();
	~Utils();
	static void WStrToUTF8(std::string& dest, const std::wstring& src);
	static std::string WStrToUTF8(const std::wstring& str);
};

