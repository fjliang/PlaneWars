#include "BulletLayer.h"
#include "PlaneLayer.h"


BulletLayer::BulletLayer()
{
	 
}

BulletLayer::~BulletLayer()
{
	 
}
SpriteBatchNode* bulletBatchNode;
bool BulletLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());
		bulletBatchNode = SpriteBatchNode::create("ui/shoot/bullet1.png");
		this->addChild(bulletBatchNode);

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

void BulletLayer::bulletMoveFinished(Node* pSender){
	Sprite* bullet = (Sprite*)pSender;
	removeBullet(bullet);
}

void BulletLayer::startShoot(float delay){

	this->schedule(schedule_selector(BulletLayer::addBullet), 0.2f, kRepeatForever, delay);

}

void BulletLayer::removeBullet(Sprite* bullet){
	if (bullet != NULL){
		this->m_pAllBullet.eraseObject(bullet);
		bulletBatchNode->removeChild(bullet, true);
	}
}

void BulletLayer::bulletMove(Sprite* bullet){
	//屏幕高度
	float screenHeight = Director::sharedDirector()->getWinSize().height;
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
 