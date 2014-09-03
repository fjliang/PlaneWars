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
 
		SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_music.mp3",true);
		WelcomeLayer* welcome= WelcomeLayer::create();
		this->addChild(welcome);
		schedule(schedule_selector(WelcomeScene::switchScene), 0, 0, 2);

		bRet = true;
	} while (0);
	return bRet;
}

void WelcomeScene::switchScene(float dt){
	auto transition= TransitionCrossFade::create(0.2, GameScene::create());
	Director::getInstance()->replaceScene(transition);
}