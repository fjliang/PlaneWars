#include "WelcomeScene.h"


WelcomeScene::WelcomeScene()
{
}

WelcomeScene::~WelcomeScene()
{
}
bool WelcomeScene::init(){
	bool bRet = false;
	do{

		WelcomeLayer* welcome= WelcomeLayer::create();
		this->addChild(welcome);
		  
		schedule(schedule_selector(WelcomeScene::switchScene), 0, 0, 2);

		bRet = true;
	} while (0);
	return bRet;
}

void WelcomeScene::switchScene(float dt){

	Director::getInstance()->replaceScene(GameScene::create());
}