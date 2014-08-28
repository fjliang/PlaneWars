#include "BombLayer.h"


BombLayer::BombLayer()
{
}
BombLayer::~BombLayer()
{
}
bool BombLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());
		this->bombNumber = 3;
		//bomb = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb.png"));

		MenuItemImage* bomb = MenuItemImage::create("ui/shoot/bomb.png",
			"ui/shoot/bomb.png", CC_CALLBACK_1(BombLayer::bobmUp, this));
		bomb->setAnchorPoint(ccp(0, 0));
		auto menu = Menu::create(bomb, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu);
		//bomb¸öÊý
		number = Label::createWithTTF(setBomb(this->bombNumber), "fonts/MarkerFelt.ttf", 50.0f);
		number->setAnchorPoint(ccp(0, 0));
		number->setPosition(ccp(bomb->getContentSize().width*1.2, 0));
		this->addChild(number);
		bRet = true;
	} while (0);
	return bRet;

}
string BombLayer::setBomb(int number){
	std::stringstream ss;
	ss << "X " << number;
	return ss.str();
}
int BombLayer::getBobm(){
	return this->bombNumber;
}
void BombLayer::bobmUp(Ref* pSender){

	if (getBobm() > 0){
		this->bombNumber--;
		number->setString(setBomb(getBobm()));

	}
}