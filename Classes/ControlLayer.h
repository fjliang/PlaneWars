#pragma once
#include"cocos2d.h"
USING_NS_CC;
class ControlLayer : public cocos2d::Layer
{
public:
	ControlLayer();
	~ControlLayer();
	CREATE_FUNC(ControlLayer); 
	bool init();
	void menuPauseCallback(Ref* pSender);
	void updateScore(int score);
};