#include "WelcomeLayer.h"

WelcomeLayer::WelcomeLayer()
{
}
WelcomeLayer::~WelcomeLayer()
{
}

bool WelcomeLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());
		Size size=Director::getInstance()->getWinSize();

		//加入全局cache中
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");

		Sprite* backGround=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png"));
		Sprite* title = Sprite::create("ui/shoot_background/shoot_copyright.png");
		Sprite* loading = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));

		backGround->setPosition(ccp(size.width / 2, size.height / 2));
		title->setPosition(ccp(size.width / 2, size.height/2 + title->getContentSize().height ));
		loading->setPosition(ccp(backGround->getContentSize().width / 2, title->getPosition().y - title->getContentSize().height / 2 - loading->getContentSize().height / 2));

		Animation* animation=	Animation::create();
		animation->setDelayPerUnit(0.3f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));
		
		Repeat* repeat=Repeat::create(Animate::create(animation), 2);
		loading->runAction(repeat);

		backGround->addChild(title);
		backGround->addChild(loading);
		this->addChild(backGround);
		bRet = true;
	} while (0);
	return bRet;
}

bool WelcomeLayer::isExistHistroy(){
	 
	if (!UserDefault::getInstance()->getBoolForKey("histroy")){
		UserDefault::getInstance()->setBoolForKey("histroy", false);
		UserDefault::getInstance()->setIntegerForKey("highestScore",0);
		UserDefault::getInstance()->flush();
		return false;
	}
	return true;

}

void WelcomeLayer::getHighestHistroyScore(){
	if (isExistHistroy()){
		GameOverLayer::highestScore= UserDefault::getInstance()->getIntegerForKey("highestScore");
	}
}