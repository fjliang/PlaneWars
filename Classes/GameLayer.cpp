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
		//����ȫ��cache��
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot_background.plist");
		SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ui/shoot.plist");

		background1 = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("background.png"));
		background1->setAnchorPoint(ccp(0, 0));
		background1->setPosition(ccp(0, 0));
		this->addChild(background1);

		background2 = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("background.png"));
		background2->setAnchorPoint(ccp(0, 0));
		background2->setPosition(ccp(0, background2->getContentSize().height - 2));//�����2��Ŀ����Ϊ�˷�ֹͼƬ����ĺ���
		this->addChild(background2);
		this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f);

		//�ɻ�ͼ��
		this->_planeLayer = PlaneLayer::createPlane();
		this->addChild(_planeLayer,100);

		//�ӵ�ͼ��
		this->_bulletLayer = BulletLayer::create();
		this->addChild(_bulletLayer);
		this->_bulletLayer->startShoot(0);
		this->setTouchEnabled(true);

		//�л�ͼ��
		this->_enemyLayer1 = new EnemyLayer("enemy1.png", EnemyLayer::maxLIFE1, 2);
		this->addChild(_enemyLayer1);
		_enemyLayer1->addEnemy();

		this->_enemyLayer2 = new EnemyLayer("enemy2.png", EnemyLayer::maxLIFE2, 4);
		this->addChild(_enemyLayer2);
		_enemyLayer2->addEnemy();

		this->_enemyLayer3 = new EnemyLayer("enemy3_n1.png", EnemyLayer::maxLIFE3, 6);
		this->addChild(_enemyLayer3);
		_enemyLayer3->addEnemy();

		scheduleUpdate();

		bRet = true;

	} while (0);

	return bRet;
}

//��������
void GameLayer::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	if (background2->getPositionY() == 0)//Ҫע����Ϊ����ͼ�߶���842������ÿ�μ�ȥ2�����Ե���0�����米���߶���841����ô���������Զ�ﲻ��������ʧ��
	{
		background1->setPositionY(0);
	}

}

void GameLayer::update(float dt){
	collisionDetection();
}


//��ײ���
void GameLayer::collisionDetection(){
 
	Vector<Sprite*> boundToDelete;//��ɾ�����ӵ�
	
	for (Sprite* bullet : this->_bulletLayer->m_pAllBullet){
		Rect boundRect = bullet->getBoundingBox();
		Vector<Enemy*> enemyToDelete;//��ɾ���ĵл�
		for (Enemy* enemy1 : this->_enemyLayer1->m_pAllEnemy){
			Rect enemyRect = enemy1->getBoundingBox();
			if (enemyRect.intersectsRect(boundRect)){
				enemy1->loseLife();
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


	//CCARRAY_FOREACH(this->_bulletLayer->m_pAllBullet, bt){
	//	Sprite* bullet = (Sprite*)bt;
	//	Array* enemyToDelete = Array::create();//�����еĵл�
	//	enemyToDelete->retain();
	//	Rect boundRect = bullet->getBoundingBox();
	//	CCARRAY_FOREACH(this->_enemyLayer1->m_pAllEnemy, e1){
	//		EnemyLayer* enemy1 = (EnemyLayer*)e1;
	//		Rect enemyRect = enemy1->getBoundingBox();
	//		if (boundRect.intersectsRect(enemyRect)){
	//			enemy1->loseLife();
	//			boundToDelete->addObject(bullet);
	//			enemyToDelete->addObject(enemy1);
	//		}

	//	}

	//	CCARRAY_FOREACH(enemyToDelete, e1){
	//		EnemyLayer* enemy1 = (EnemyLayer*)e1;
	//		enemy1->enemyBlowup(enemy1);
	//	}
	//}
	//CCARRAY_FOREACH(boundToDelete, bt){
	//	Sprite* bullet = (Sprite*)bt;
	//	this->_bulletLayer->removeBullet(bullet);
	//}
}
