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
		this->addChild(plane, 0, AIRPLANE); //AIRPLANE 是tag
		Blink* blink=Blink::create(1, 3);  //闪烁动画
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
		sharedPlane = pRet;//获得静态指针sharedPlane的值
		 
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
	pTouchListener->setSwallowTouches(true); //是否向下传递触摸
	pTouchListener->setEnabled(true);
	
	//通过 lambda 表达式 直接实现触摸事件的回掉方法
	pTouchListener->onTouchBegan = [](Touch* touch, Event* event){
		log("onTouchBegan");
		return true;
	};

	pTouchListener->onTouchMoved = [](Touch* touch, Event* event){
		log("onTouchMoved");
		//是否存活
		if (isAlive){
			Point beginPoint = touch->getLocationInView();
			beginPoint = Director::sharedDirector()->convertToGL(beginPoint);
			Rect planeRect = PlaneLayer::sharedPlane->getChildByTag(AIRPLANE)->boundingBox();
			planeRect.origin.x -= 15;
			planeRect.origin.y -= 15;
			//稍微加大触摸位置
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
	//飞机及游戏状态判断
	if (isAlive&&!pDirector->isPaused()){
		//边界判断
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
