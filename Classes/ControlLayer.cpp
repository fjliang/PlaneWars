#include "ControlLayer.h"

ControlLayer::ControlLayer()
{
}

ControlLayer::~ControlLayer()
{
}
MenuItemImage* pauseItem;
Label* scoreLabel;
bool ControlLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());
		Size size= Director::getInstance()->getWinSize();
		pauseItem = MenuItemImage::create();
		pauseItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_nor.png"));
		pauseItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_pressed.png"));
		pauseItem->setCallback(CC_CALLBACK_1(ControlLayer::menuPauseCallback, this));
		pauseItem->setPosition(ccp(30, size.height - 30));
		auto menu = Menu::create(pauseItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu);

		scoreLabel = Label::createWithTTF("0", "fonts/MarkerFelt.ttf", 40.0f );
		scoreLabel->setString("0");
		scoreLabel->setPosition(pauseItem->getContentSize().width / 2 + 80, size.height - 30);
		this->addChild(scoreLabel);
		bRet = true;
	} while (0);
	return bRet;
}

void ControlLayer::menuPauseCallback(Ref* pSender){
	
	if (Director::getInstance()->isPaused()){
		pauseItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_nor.png"));
		pauseItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_pressed.png"));
		Director::getInstance()->resume();
	}
	else{
		pauseItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_nor.png"));
		pauseItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_pressed.png"));
		Director::getInstance()->pause();
	}
}

void ControlLayer::updateScore(int score){
	
	scoreLabel->setString(String::createWithFormat("%d", score)->_string);
}