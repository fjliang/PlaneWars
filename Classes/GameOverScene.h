#pragma once
#include"cocos2d.h"
#include"GameOverLayer.h"
USING_NS_CC;
class GameOverScene : public Scene
{
public:
	GameOverScene();
	~GameOverScene();
	CREATE_FUNC(GameOverScene);
	bool init();
};

