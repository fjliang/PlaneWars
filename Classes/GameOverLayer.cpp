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

		int histroyHighestScore = UserDefault::getInstance()->getIntegerForKey("highestScore",0);

		Dictionary* dictionary = Dictionary::createWithContentsOfFile("string.xml");
		
		auto str = String::createWithFormat("%s%d", ((String*)dictionary->objectForKey("message"))->_string, histroyHighestScore);
		LabelTTF* labelHistroy = LabelTTF::create(str->_string, "Arial", 40);
		/*labelHistroy->setString(str->_string);
		labelHistroy->setSystemFontSize(40);*/
 		labelHistroy->setPosition(ccp(10 + labelHistroy->getContentSize().width / 2, size.height - 10 - labelHistroy->getContentSize().height / 2));
 
		auto currentScore = String::createWithFormat("%d", highestScore);
		Label* labelScore = Label::createWithTTF(currentScore->_string, "fonts/MarkerFelt.ttf", 60);
		labelScore->setPosition(ccp(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2 - labelScore->getContentSize().height ));


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