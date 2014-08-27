#include "GameLayer.h"

USING_NS_CC;

Sprite* background1;
Sprite* background2;

GameLayer::GameLayer()
{
}

GameLayer::~GameLayer()
{
}
bool GameLayer::init()
{
	bool bRet = false;
	do{
		CC_BREAK_IF(!Layer::init());
		//加入全局cache中
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");

		background1 = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("background.png"));
		background1->setAnchorPoint(ccp(0, 0));
		background1->setPosition(ccp(0, 0));
		this->addChild(background1);

		background2 = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("background.png"));
		background2->setAnchorPoint(ccp(0, 0));
		background2->setPosition(ccp(0, background2->getContentSize().height - 2));//这里减2的目的是为了防止图片交界的黑线
		this->addChild(background2);
		this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f);

		//飞机图层
		this->_planeLayer = PlaneLayer::createPlane();
		this->addChild(_planeLayer,100);

		//子弹图层
		this->_bulletLayer = BulletLayer::create();
		this->addChild(_bulletLayer);
		this->_bulletLayer->startShoot(0);
		this->setTouchEnabled(true);

		//敌机图层
		this->_enemyLayer1 = new EnemyLayer("enemy1.png", EnemyLayer::maxLIFE1, 1);
		this->addChild(_enemyLayer1);
		_enemyLayer1->addEnemy();

		this->_enemyLayer2 = new EnemyLayer("enemy2.png", EnemyLayer::maxLIFE2, 3);
		this->addChild(_enemyLayer2);
		_enemyLayer2->addEnemy();

		this->_enemyLayer3 = new EnemyLayer("enemy3_n1.png", EnemyLayer::maxLIFE3, 5);
		
		this->addChild(_enemyLayer3);
		_enemyLayer3->addEnemy();

		scheduleUpdate();

		bRet = true;

	} while (0);

	return bRet;
}

//背景滚动
void GameLayer::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	if (background2->getPositionY() == 0)//要注意因为背景图高度是842，所以每次减去2最后可以到达0，假如背景高度是841，那么这个条件永远达不到，滚动失败
	{
		background1->setPositionY(0);
	}

}

void GameLayer::update(float dt){
	collisionDetection();
}


//碰撞检测
void GameLayer::collisionDetection(){
 
	Vector<Sprite*> boundToDelete;//待删除的子弹
	
	//enemy1
	for (Sprite* bullet : this->_bulletLayer->m_pAllBullet){
		Rect boundRect = bullet->getBoundingBox();
		Vector<Enemy*> enemyToDelete;//待删除的敌机
		for (Enemy* enemy1 : this->_enemyLayer1->m_pAllEnemy){
			Rect enemyRect = enemy1->getBoundingBox();
			if (enemyRect.intersectsRect(boundRect)){
				boundToDelete.pushBack(bullet);
				enemyToDelete.pushBack(enemy1);
			}
		}

		for (Enemy* enemy1 : enemyToDelete){
			_enemyLayer1->enemyBlowup(enemy1);
		}

	}
	for (Sprite* bullet : boundToDelete){
		this->_bulletLayer->removeBullet(bullet);
	}
	//enemy2
	boundToDelete.clear();
	for (Sprite* bullet : this->_bulletLayer->m_pAllBullet){
		Rect boundRect = bullet->getBoundingBox();
		Vector<Enemy*> enemyToDelete;//待删除的敌机
		for (Enemy* enemy2 : this->_enemyLayer2->m_pAllEnemy){
			Rect enemyRect = enemy2->getBoundingBox();
			if (enemyRect.intersectsRect(boundRect)){
				enemy2->loseLife();
				enemy2->getEnemy()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_hit.png"));
				if (enemy2->getLife()<=0){
					enemyToDelete.pushBack(enemy2);
				}
				boundToDelete.pushBack(bullet);
			}
		}

		for (Enemy* enemy2 : enemyToDelete){
			_enemyLayer2->enemyBlowup(enemy2);
		}

	}
	for (Sprite* bullet : boundToDelete){
		this->_bulletLayer->removeBullet(bullet);
	}
	//enemy3
	boundToDelete.clear();
	for (Sprite* bullet : this->_bulletLayer->m_pAllBullet){
		Rect boundRect = bullet->getBoundingBox();
		Vector<Enemy*> enemyToDelete;//待删除的敌机
		for (Enemy* enemy3 : this->_enemyLayer3->m_pAllEnemy){
			Rect enemyRect = enemy3->getBoundingBox();
			if (enemyRect.intersectsRect(boundRect)){
				enemy3->loseLife();
				enemy3->getEnemy()->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_hit.png"));
				if (enemy3->getLife() <= 0){
					enemyToDelete.pushBack(enemy3);
				}
				boundToDelete.pushBack(bullet);
			}
		}

		for (Enemy* enemy3 : enemyToDelete){
			_enemyLayer3->enemyBlowup(enemy3);
		}

	}
	for (Sprite* bullet : boundToDelete){
		this->_bulletLayer->removeBullet(bullet);
	}
 
}
