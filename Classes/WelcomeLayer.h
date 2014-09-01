#pragma once
#include"cocos2d.h"
#include"GameOverLayer.h"
USING_NS_CC;
class WelcomeLayer : public cocos2d::Layer
{
public:
	WelcomeLayer();
	~WelcomeLayer();
	CREATE_FUNC(WelcomeLayer);
	bool init();
	bool isExistHistroy();
	void getHighestHistroyScore();
};


