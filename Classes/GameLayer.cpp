#include "GameLayer.h"

USING_NS_CC;

Sprite* background1;
Sprite* background2;
Label* bombLabel;
UFOLayer* ufo1;
UFOLayer* ufo2;
int GameLayer::bombNumber = 3;
int score = 0;
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

		background1 = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("background.png"));
		background1->setAnchorPoint(ccp(0, 0));
		background1->setPosition(ccp(0, 0));
		this->addChild(background1);

		background2 = Sprite::createWithSpriteFrame(SpriteFrameCache::sharedSpriteFrameCache()->getSpriteFrameByName("background.png"));
		background2->setAnchorPoint(ccp(0, 0));
		background2->setPosition(ccp(0, background2->getContentSize().height - 2));//这里减2的目的是为了防止图片交界的黑线
		this->addChild(background2);
		this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f);

		//bomb道具
		initBomb();

		//UFO1
		ufo1 = new UFOLayer("ufo1.png");
		this->addChild(ufo1);
		ufo1->startUFO();

		//UFO2
		ufo2 = new UFOLayer("ufo2.png");
		this->addChild(ufo2);
		ufo2->startUFO();

		//飞机图层
		this->_planeLayer = PlaneLayer::createPlane();
		this->addChild(_planeLayer, 100);

		//子弹图层
		this->_bulletLayer = BulletLayer::create();
		this->addChild(_bulletLayer);
		this->_bulletLayer->startShoot(0);
		this->setTouchEnabled(true);

		//敌机图层
		this->_enemyLayer1 = new EnemyLayer("enemy1.png", GameConfig::maxLIFE1, GameConfig::ENEMY1_DT);
		this->addChild(_enemyLayer1);
		_enemyLayer1->addEnemy();

		this->_enemyLayer2 = new EnemyLayer("enemy2.png", GameConfig::maxLIFE2, GameConfig::ENEMY2_DT);
		this->addChild(_enemyLayer2);
		_enemyLayer2->addEnemy();

		this->_enemyLayer3 = new EnemyLayer("enemy3_n1.png", GameConfig::maxLIFE3, GameConfig::ENEMY3_DT);

		this->addChild(_enemyLayer3);
		_enemyLayer3->addEnemy();

		//控制层
		control= ControlLayer::create();
		this->addChild(control,101);


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

void GameLayer::initBomb(){
	MenuItemImage* bomb = MenuItemImage::create("ui/shoot/bomb.png",
		"ui/shoot/bomb.png", CC_CALLBACK_1(GameLayer::bobmUp, this));
	bomb->setAnchorPoint(ccp(0, 0));
	Menu* bombMenu = Menu::create(bomb, NULL);
	bombMenu->setPosition(Vec2::ZERO);          
	this->addChild(bombMenu, 101);
	//bomb个数
	bombLabel = Label::createWithTTF(setBomb(this->bombNumber), "fonts/MarkerFelt.ttf", 50.0f);
	bombLabel->setAnchorPoint(ccp(0, 0));
	bombLabel->setPosition(ccp(bomb->getContentSize().width*1.2, 0));
	this->addChild(bombLabel, 101);
}

string GameLayer::setBomb(int number){
	std::stringstream ss;
	ss << "X " << number;
	return ss.str();
}

void GameLayer::bobmUp(Ref* pSender){

	if (!Director::getInstance()->isPaused() && this->_planeLayer->isAlive && this->bombNumber > 0){
		this->bombNumber--;
		bombLabel->setString(setBomb(this->bombNumber));

		score += _enemyLayer1->m_pAllEnemy.size()*GameConfig::ENEMY1_SCORE;
		score += _enemyLayer2->m_pAllEnemy.size()*GameConfig::ENEMY2_SCORE;
		score += _enemyLayer3->m_pAllEnemy.size()*GameConfig::ENEMY3_SCORE;

		this->_enemyLayer1->removeAllEnemy(_enemyLayer1->m_pAllEnemy);
		this->_enemyLayer2->removeAllEnemy(_enemyLayer2->m_pAllEnemy);
		this->_enemyLayer3->removeAllEnemy(_enemyLayer3->m_pAllEnemy);

		this->control->updateScore(score);
	}
}

void GameLayer::update(float dt){
	collisionDetection();
}

void GameLayer::removePlane(float dt){
	this->removeChild(this->_planeLayer, true);
	GameOverLayer::highestScore = score;

	auto fade= TransitionCrossFade::create(0.2, GameOverScene::create());
	Director::getInstance()->replaceScene(fade);
	this->cleanup();

}


//碰撞检测
void GameLayer::collisionDetection(){

	//检测飞机是否相撞
	Rect planeRect = Rect();
	if (this->_planeLayer->isAlive){
		planeRect = this->_planeLayer->getChildByTag(PlaneLayer::AIRPLANE)->getBoundingBox();
	}

	Vector<Sprite*> boundToDelete;//待删除的子弹

	//enemy1
	for (Sprite* bullet : this->_bulletLayer->m_pAllBullet){
		Rect boundRect = bullet->getBoundingBox();
		Vector<Enemy*> enemyToDelete;//待删除的敌机
		for (Enemy* enemy1 : this->_enemyLayer1->m_pAllEnemy){
			Rect enemyRect = enemy1->getBoundingBox();
			if (enemyRect.intersectsRect(boundRect)){
				enemy1->loseLife();
				boundToDelete.pushBack(bullet);
				enemyToDelete.pushBack(enemy1);
			}

			if (this->_planeLayer->isAlive&&enemyRect.intersectsRect(planeRect) && enemy1->getLife() > 0){
				this->_planeLayer->isAlive = false;
			}
		}

		for (Enemy* enemy1 : enemyToDelete){
			_enemyLayer1->enemyBlowup(enemy1);
			score += GameConfig::ENEMY1_SCORE;
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
				if (enemy2->getLife() <= 0){
					enemyToDelete.pushBack(enemy2);
				}
				boundToDelete.pushBack(bullet);
			}
			if (this->_planeLayer->isAlive&&enemyRect.intersectsRect(planeRect) && enemy2->getLife() > 0){
				this->_planeLayer->isAlive = false;
			}
		}

		for (Enemy* enemy2 : enemyToDelete){
			_enemyLayer2->enemyBlowup(enemy2);
			score += GameConfig::ENEMY2_SCORE;
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
			if (this->_planeLayer->isAlive&&enemyRect.intersectsRect(planeRect) && enemy3->getLife() > 0){
				this->_planeLayer->isAlive = false;
			}
		}

		for (Enemy* enemy3 : enemyToDelete){
			_enemyLayer3->enemyBlowup(enemy3);
			score += GameConfig::ENEMY3_SCORE;
		}

	}
	for (Sprite* bullet : boundToDelete){
		this->_bulletLayer->removeBullet(bullet);
	}

	//飞机爆炸
	if (!this->_planeLayer->isAlive&&!GameConfig::GAME_OVER){
		GameConfig::GAME_OVER = true;
		this->_bulletLayer->stopShoot();
		this->_bulletLayer->stopBlue(0);
		Sprite*	plane = (Sprite*)this->_planeLayer->getChildByTag(PlaneLayer::AIRPLANE);
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.08f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
		Animate* blowup = Animate::create(animation);
		FiniteTimeAction* remove = CallFuncN::create(CC_CALLBACK_0(GameLayer::removePlane, this, 0));
		plane->runAction(Sequence::create(blowup, remove, NULL));

	}

	//检测炸弹UFO
	Vector<Sprite*> vector_ufo = ufo2->vector_ufo;
	if (_planeLayer->isAlive){
		for (Sprite* ufo : vector_ufo){
			Rect ufoRect = ufo->getBoundingBox();
			if (ufoRect.intersectsRect(planeRect)){
				ufo2->removeUFO(ufo);
				this->bombNumber++;
				bombLabel->setString(setBomb(this->bombNumber));
			}
		}
	}
	//检测子弹UFO
	vector_ufo = ufo1->vector_ufo;
	if (_planeLayer->isAlive){
		for (Sprite* ufo : vector_ufo){
			Rect ufoRect = ufo->getBoundingBox();
			if (ufoRect.intersectsRect(planeRect)){
				ufo1->removeUFO(ufo);
				this->_bulletLayer->startBlueShoot(0);

				this->_bulletLayer->stopBlueShoot();

			}
		}
	}

	this->control->updateScore(score);


}
