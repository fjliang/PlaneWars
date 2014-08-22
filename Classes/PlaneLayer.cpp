#include "PlaneLayer.h"

PlaneLayer::PlaneLayer()
{
}

PlaneLayer::~PlaneLayer()
{
}
 
PlaneLayer* PlaneLayer::sharedPlane = NULL;
bool PlaneLayer::isAlive = true;

bool PlaneLayer::init(){
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());
		Size winSize=	Director::sharedDirector()->getWinSize();
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("/ui/shoot.plist");
 
		Sprite* plane = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("hero1.png"));
		plane->setPosition(ccp(winSize.width / 2, plane->getContentSize().height/2));
		this->addChild(plane, 0, AIRPLANE); //AIRPLANE ��tag
		Blink* blink=Blink::create(1, 3);  //��˸����
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("hero1.png"));
		animation->addSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("hero2.png"));
		Animate* animate=Animate::create(animation);

		plane->runAction(blink);
		plane->runAction(RepeatForever::create(animate));

		bRet = true;
	} while (0);
	return bRet;
}

PlaneLayer* PlaneLayer::createPlane()
{
	PlaneLayer* pRet = new PlaneLayer();
	if (pRet&&pRet->init()){
		pRet->autorelease();
		sharedPlane = pRet;//��þ�ָ̬��sharedPlane��ֵ
		 
		pRet->initTouchEvent();
		return pRet;
	}
	else{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}

}

void PlaneLayer::initTouchEvent(){
 
	EventListenerTouchOneByOne* pTouchListener=EventListenerTouchOneByOne::create();
	pTouchListener->setSwallowTouches(true); //�Ƿ����´��ݴ���
	pTouchListener->setEnabled(true);
	
	//ͨ�� lambda ���ʽ ֱ��ʵ�ִ����¼��Ļص�����
	pTouchListener->onTouchBegan = [](Touch* touch, Event* event){
		log("onTouchBegan");
		return true;
	};

	pTouchListener->onTouchMoved = [](Touch* touch, Event* event){
		log("onTouchMoved");
		//�Ƿ���
		if (isAlive){
			Point beginPoint = touch->getLocationInView();
			beginPoint = Director::sharedDirector()->convertToGL(beginPoint);
			Rect planeRect = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->boundingBox();
			planeRect.origin.x -= 15;
			planeRect.origin.y -= 15;
			//��΢�Ӵ���λ��
			planeRect.size.width += 30;
			planeRect.size.height += 30;
			if (planeRect.containsPoint(beginPoint)){
			Point endPoint=touch->getPreviousLocationInView();
			endPoint = Director::sharedDirector()->convertToGL(endPoint);
			Point offset = ccpSub(beginPoint, endPoint);
			Point toPoint=ccpAdd(PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->getPosition(),offset);
			PlaneLayer::sharedPlane->moveTo(toPoint);
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(pTouchListener, this->sharedPlane);
}

void PlaneLayer::moveTo(Point location){
	Director* pDirector=Director::sharedDirector();
	//�ɻ�����Ϸ״̬�ж�
	if (isAlive&&!pDirector->isPaused()){
		//�߽��ж�
		Point actualPoint;
		Size winSize= pDirector->getWinSize();
		Size planeSize=this->getChildByTag(AIRPLANE)->getContentSize();
		if (location.x<planeSize.width / 2){
			location.x = planeSize.width / 2;
		}
		if (location.x>winSize.width -planeSize.width/ 2){
			location.x = winSize.width - planeSize.width / 2;
		}
		if (location.y<planeSize.height / 2){
			location.y = planeSize.height / 2;
		}
		if (location.y>winSize.height - planeSize.height / 2){
			location.y=winSize.height - planeSize.height / 2;
		}
		this->getChildByTag(AIRPLANE)->setPosition(location);
	}
}
