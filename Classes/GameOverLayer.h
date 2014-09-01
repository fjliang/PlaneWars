#pragma once
#include"cocos2d.h"
USING_NS_CC;
class GameOverLayer : public cocos2d::Layer
{
public:
	GameOverLayer();
	~GameOverLayer();
	bool init();
	static int highestScore;
};


