#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
USING_NS_CC;
 
class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	CREATE_FUNC(GameScene);
	virtual bool init();
	GameLayer* _gameLayer;//��gamelayer��¶��GameScene
};

