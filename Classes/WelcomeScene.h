#pragma once
#include"cocos2d.h"
#include "WelcomeLayer.h"
#include "GameScene.h"

USING_NS_CC;
class WelcomeScene : public Scene
{
public:
	WelcomeScene();
	~WelcomeScene();
	CREATE_FUNC(WelcomeScene);
	bool init();
	void switchScene(float dt);
};

