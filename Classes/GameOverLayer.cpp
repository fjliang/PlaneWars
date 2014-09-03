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
		Size size=Director::getInstance()->getWinSize();
		Sprite* sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gameover.png"));
		sprite->setPosition(ccp(sprite->getContentSize().width/2,size.height/2));

		//Utils::WStrToUTF8(L"历史最高分")
		int histroyHighestScore = UserDefault::getInstance()->getIntegerForKey("highestScore",0);
		Dictionary* dictionary = Dictionary::createWithContentsOfFile("string.xml");
		auto str = String::createWithFormat("%d", histroyHighestScore);
		LabelTTF* labelHistroy = LabelTTF::create(((String*)dictionary->objectForKey("message"))->_string + str->_string, "Arial", 20);
 		labelHistroy->setPosition(ccp(10 + labelHistroy->getContentSize().width / 2, size.height - 50 - labelHistroy->getContentSize().height ));
 
		auto currentScore = String::createWithFormat("%d", highestScore);
		Label* labelScore = Label::createWithTTF(currentScore->_string, "fonts/MarkerFelt.ttf", 60);
		labelScore->setPosition(ccp(size.width / 2, size.height / 2 + labelScore->getContentSize().height / 2 ));

		if (highestScore>histroyHighestScore){
			UserDefault::getInstance()->setIntegerForKey("highestScore", highestScore);
			UserDefault::getInstance()->flush();
		}

		this->addChild(sprite);
		this->addChild(labelHistroy);
		this->addChild(labelScore);

		bRet = true;
	} while (0);
	return bRet;
}