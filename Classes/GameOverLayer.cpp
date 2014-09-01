#include "GameOverLayer.h"

GameOverLayer::GameOverLayer()
{
}
GameOverLayer::~GameOverLayer()
{
}

int GameOverLayer::highestScore = 0;
bool GameOverLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());


		bRet = true;
	} while (0);
	return bRet;
}