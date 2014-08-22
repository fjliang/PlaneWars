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
		_gameLayer = GameLayer::create();//��ȡgameLayerʵ��
		CC_BREAK_IF(!_gameLayer);
		this->addChild(_gameLayer);//��gameLayer�ӵ�������
		bRet = true;
	} while (0);
	 
	return bRet;
}