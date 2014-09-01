#include "WelcomeLayer.h"

WelcomeLayer::WelcomeLayer()
{
}
WelcomeLayer::~WelcomeLayer()
{
}

bool WelcomeLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());


		bRet = true;
	} while (0);
	return bRet;
}