#include "GameScene.h"

GameScene::GameScene()
{
	_gameLayer = NULL;
}

GameScene::~GameScene()
{
}

bool GameScene::init()
{
	bool bRet = false;
	do{
		
		CC_BREAK_IF(!Scene::init());
		_gameLayer = GameLayer::create();//获取gameLayer实例
		CC_BREAK_IF(!_gameLayer);
		this->addChild(_gameLayer);//把gameLayer加到场景中
		bRet = true;
	} while (0);
	 
	return bRet;
}