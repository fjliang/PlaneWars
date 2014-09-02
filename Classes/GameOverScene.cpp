#include "GameOverScene.h"


GameOverScene::GameOverScene()
{
}


GameOverScene::~GameOverScene()
{
}
bool GameOverScene::init(){
	bool bRet = false;
	do{
	
		this->addChild(GameOverLayer::create());

		bRet = true;
	} while (0);
	return bRet;
}