#include "UFOLayer.h"


UFOLayer::UFOLayer(string ufoPng)
{
	this->ufoPng = ufoPng;
	spriteBatchNode = SpriteBatchNode::create("ui/shoot/" + ufoPng);
	this->addChild(spriteBatchNode);
	if (ufoPng.compare("ufo1.png") == 0){
		this->dt = 10;
		this->interval = 50;
	}
	else{
		this->dt = 30;
		this->interval = 70;
	}
}

UFOLayer::~UFOLayer()
{
}
bool UFOLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());
		bRet = true;
	} while (0);
	return bRet;
}

void UFOLayer::addUFO(float dt){
	Sprite* ufo = Sprite::createWithTexture(this->spriteBatchNode->getTexture());
	Size winSize = Director::getInstance()->getWinSize();
	int minX = ufo->getContentSize().width / 2;
	int maxX = winSize.width - ufo->getContentSize().width / 2;
	int rangeX = maxX - minX;
	int actualX = rand() % rangeX + minX;
	int actualY = winSize.height + ufo->getContentSize().height / 2;
	ufo->setPosition(ccp(actualX, actualY));
	spriteBatchNode->addChild(ufo);
	vector_ufo.pushBack(ufo);

	ccBezierConfig bezierConfig ;
	bezierConfig.controlPoint_1 = ccp(actualX, actualY);
	actualX = rand() % rangeX + minX;
	bezierConfig.controlPoint_2 = ccp(actualX, winSize.height / 2);
	actualX = rand() % rangeX + minX;
	bezierConfig.endPosition = ccp(actualX, -ufo->getContentSize().height / 2);
	int rangeDuration = GameConfig::ENEMY_MAX_SPEED - GameConfig::ENEMY_MIN_SPEED;
	int actualDuration = rand() % rangeDuration + GameConfig::ENEMY_MIN_SPEED;
	BezierTo* bezierTo= BezierTo::create(actualDuration, bezierConfig);
	CallFuncN* remove=CallFuncN::create(CC_CALLBACK_0(UFOLayer::removeUFO, this, ufo));
	Sequence* sequence = Sequence::create(bezierTo, remove, NULL);

	ufo->runAction(sequence);
}
void UFOLayer::removeUFO(Sprite* ufo){
	vector_ufo.eraseObject(ufo);
	spriteBatchNode->removeChild(ufo,true);
}
void UFOLayer::startUFO(){
	schedule(schedule_selector(UFOLayer::addUFO), this->interval, kRepeatForever, this->dt);
}

