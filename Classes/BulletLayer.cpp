#include "BulletLayer.h"
#include "PlaneLayer.h"


BulletLayer::BulletLayer()
{

}

BulletLayer::~BulletLayer()
{

}


bool BulletLayer::init(){
	bool bRet = false;
	do{

		CC_BREAK_IF(!Layer::init());
		bulletBatchNode = SpriteBatchNode::create("ui/shoot/bullet1.png");
		blueBulletBatchNode = SpriteBatchNode::create("ui/shoot/bullet2.png");
		this->addChild(bulletBatchNode);
		this->addChild(blueBulletBatchNode);

		bRet = true;
	} while (0);
	return bRet;
}
void BulletLayer::addBullet(float dt){
	Sprite* bullet = Sprite::createWithTexture(bulletBatchNode->getTexture());
	bulletBatchNode->addChild(bullet);

	Node* pLayer = PlaneLayer::sharedPlane->getChildByTag(PlaneLayer::AIRPLANE);
	Point planePostion = pLayer->getPosition();
	Point bulletPostion = ccp(planePostion.x, planePostion.y + pLayer->getContentSize().height / 2);
	bullet->setPosition(bulletPostion);
	m_pAllBullet.pushBack(bullet);
	bulletMove(bullet);
}

void BulletLayer::addBlueBullet(float dt){

	Sprite* bulletLeft = Sprite::createWithTexture(blueBulletBatchNode->getTexture());
	Sprite* bulletRight = Sprite::createWithTexture(blueBulletBatchNode->getTexture());

	Node* plane = PlaneLayer::sharedPlane->getChildByTag(PlaneLayer::AIRPLANE);
	Point planePostion = plane->getPosition();

	Point bulletLeftPostion = ccp(planePostion.x - plane->getContentSize().width / 3, planePostion.y);
	bulletLeft->setPosition(bulletLeftPostion);
	blueBulletBatchNode->addChild(bulletLeft);
	m_pAllBullet.pushBack(bulletLeft);
	bulletMove(bulletLeft);

	Point bulletRightPostion = ccp(planePostion.x + plane->getContentSize().width / 3, planePostion.y);
	bulletRight->setPosition(bulletRightPostion);
	blueBulletBatchNode->addChild(bulletRight);
	m_pAllBullet.pushBack(bulletRight);
	bulletMove(bulletRight);

}

void BulletLayer::bulletMoveFinished(Node* pSender){
	Sprite* bullet = (Sprite*)pSender;
	removeBullet(bullet);
}

void BulletLayer::startShoot(float delay){

	this->schedule(schedule_selector(BulletLayer::addBullet), 0.2f, kRepeatForever, delay);

}

void BulletLayer::startBlueShoot(float delay){

	this->schedule(schedule_selector(BulletLayer::addBlueBullet), 0.2f, kRepeatForever, delay);

}

void BulletLayer::removeBullet(Sprite* bullet){
	if (bullet != NULL&&this->m_pAllBullet.contains(bullet)){
		this->m_pAllBullet.eraseObject(bullet);

		if (bulletBatchNode->getChildren().contains(bullet))
			bulletBatchNode->removeChild(bullet, true);

		if (blueBulletBatchNode->getChildren().contains(bullet))
			blueBulletBatchNode->removeChild(bullet, true);

	}
}

void BulletLayer::bulletMove(Sprite* bullet){
	//屏幕高度
	float screenHeight = Director::getInstance()->getWinSize().height;
	//子弹飞行距离
	float length = screenHeight + bullet->getContentSize().height / 2 - bullet->getPosition().y;
	float velocity = 420 / 1;//飞行速度 420pix/sec
	float relaMoveDuration = length / velocity;
	FiniteTimeAction* actionMove = MoveTo::create(relaMoveDuration, ccp(bullet->getPosition().x, screenHeight + bullet->getContentSize().height / 2));
	FiniteTimeAction* actionDone = CallFuncN::create(this, callfuncN_selector(BulletLayer::bulletMoveFinished));//回调子弹结束的处理方法
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	bullet->runAction(sequence);

}

void BulletLayer::stopShoot(){
	this->unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::stopBlue(float dt){
	this->unschedule(schedule_selector(BulletLayer::addBlueBullet));
}

void BulletLayer::stopBlueShoot(){
	schedule(schedule_selector(BulletLayer::stopBlue), 0, 0, 10);
}