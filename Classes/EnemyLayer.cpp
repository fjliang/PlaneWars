#include "EnemyLayer.h"


EnemyLayer::EnemyLayer()
{
}
EnemyLayer::EnemyLayer(std::string enemyPng, int enemyLife,float dt){
 
	this->enemyLife = enemyLife;
	this->enemyPng = enemyPng;
	this->dt = dt;
	gameConfig = GameConfig::getInstance();
	 
	/*pSpriteBatchNode = SpriteBatchNode::create(enemyPng);
	addChild(pSpriteBatchNode);*/
}

EnemyLayer::~EnemyLayer()
{
}

Animation* EnemyLayer::getBlowupAnimation(Animation* animation, string enemyPng){
	if (enemyPng.compare("enemy1.png")==0){
		vector<string> enemy1 = gameConfig->vector_enemy1;
		for (string s : enemy1)
		{
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s));
		}
	}
	if (enemyPng.compare("enemy2.png") == 0){
		vector<string> enemy2 = gameConfig->vector_enemy2;
		for (string s : enemy2)
		{
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s));
		}
	}
	if (enemyPng.compare("enemy3_n1.png") == 0){
		vector<string> enemy3 = gameConfig->vector_enemy3;
		for (string s : enemy3)
		{
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(s));
		}
	}
	return animation;
}

void EnemyLayer::enemyBlowup(Enemy* enemy){
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.05f);
	Animate* blowupAnimate = Animate::create(getBlowupAnimation(animation, this->enemyPng));
	CallFuncN* removeEnemy = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeEnemy, this, enemy));
	Sequence* sequence = Sequence::create(blowupAnimate, removeEnemy, NULL);
	enemy->getEnemy()->runAction(sequence);
}

void EnemyLayer::removeEnemy(Enemy* enemy){
	 
	if (enemy!=NULL){
		//this->pSpriteBatchNode->removeChild(enemy->getEnemy(),true);
		this->removeChild(enemy->getEnemy(),true);
		m_pAllEnemy.eraseObject(enemy);
	}
}

void EnemyLayer::removeAllEnemy(Vector<Enemy*>  m_pAllEnemy){

	for (Enemy* enemy : m_pAllEnemy)
	{
		if (enemy->getLife()>0){
			enemyBlowup(enemy);
		}
	}
 
}

void EnemyLayer::enemyMoveFinished(Enemy* enemy){
	if (enemy != NULL){
		 
		this->removeChild(enemy->getEnemy(), true);
		m_pAllEnemy.eraseObject(enemy);
	}
}
void EnemyLayer::initEnemy(float dt){
	 
	//this->enemyPlane = Sprite::createWithTexture(pSpriteBatchNode->getTexture());
	this->enemyPlane = Sprite::createWithSpriteFrameName(this->enemyPng);
	Enemy* enemy = Enemy::create();
	enemy->bindSprite(enemyPlane, this->enemyLife);

	//随机初始位置
	Size enemySize = enemyPlane->getContentSize();
	Size winSize = Director::sharedDirector()->getWinSize();
	int minX = enemySize.width / 2;
	int maxX = winSize.width - enemySize.width / 2;
	//X范围
	int rangeX = maxX - minX;
	int actualX = rand() % rangeX + minX;
	enemyPlane->setPosition(ccp(actualX, winSize.height + enemySize.height / 2));
	//pSpriteBatchNode->addChild(enemyPlane);
	this->addChild(enemyPlane);
	m_pAllEnemy.pushBack(enemy);
	//随机飞行速度
	float minDuration, maxDuration;
	minDuration = GameConfig::ENEMY_MIN_SPEED;
	maxDuration = GameConfig::ENEMY_MAX_SPEED;
	//根据游戏难度赋值
	int rangeDuration = maxDuration - minDuration;
	int acturalDuration = rand() % rangeDuration + minDuration;
	FiniteTimeAction* actionMove = MoveTo::create(acturalDuration, ccp(actualX, -enemyPlane->getContentSize().height / 2));
	FiniteTimeAction* actionDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::enemyMoveFinished, this, enemy));
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	enemyPlane->runAction(sequence);

	if (this->enemyPng.compare("enemy3_n1.png")==0){
		Animation* animation = Animation::create();
		animation->setDelayPerUnit(0.05f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png"));
		enemyPlane->runAction(RepeatForever::create(Animate::create(animation)));
	}


}
void EnemyLayer::addEnemy(){
	schedule(schedule_selector(EnemyLayer::initEnemy),this->dt,kRepeatForever,0);
}
 
