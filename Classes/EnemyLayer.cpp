#include "EnemyLayer.h"


EnemyLayer::EnemyLayer()
{
}
EnemyLayer::EnemyLayer(std::string enemyPng, int enemyLife,float dt){
 
	this->enemyLife = enemyLife;
	this->enemyPng = enemyPng;
	this->dt = dt;
	enemyConfig = EnemyConfig::getInstance();
	/*pSpriteBatchNode = SpriteBatchNode::create(enemyPng);
	addChild(pSpriteBatchNode);*/
}

EnemyLayer::~EnemyLayer()
{
 
}

void EnemyLayer::enemyBlowup(Enemy* enemy){
	
	Animation* animation = Animation::create( );
	animation->setDelayPerUnit(0.1f);
	
	 

	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));
	 
	Animate* animate=Animate::create(animation);
	CallFuncN* removeEnemy = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::removeEnemy, this, enemy));
	Sequence* sequence = Sequence::create(animate,removeEnemy,NULL);
	enemy->getEnemy()->runAction(sequence);
}

void EnemyLayer::removeEnemy(Enemy* enemy){
	 
	if (enemy!=NULL){
		//this->pSpriteBatchNode->removeChild(enemy->getEnemy(),true);
		this->removeChild(enemy->getEnemy(),true);
		m_pAllEnemy.eraseObject(enemy);
	}
}

void EnemyLayer::removeAllEnemy(){

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
	minDuration = 30 / 1;
	maxDuration = 5 / 1;
	//根据游戏难度赋值
	int rangeDuration = maxDuration - minDuration;
	int acturalDuration = rand() % rangeDuration + minDuration;
	FiniteTimeAction* actionMove = MoveTo::create(acturalDuration, ccp(actualX, -enemyPlane->getContentSize().height / 2));
	 
	FiniteTimeAction* actionDone = CallFuncN::create(CC_CALLBACK_0(EnemyLayer::enemyMoveFinished, this, enemy));
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	 
	enemyPlane->runAction(sequence);
}
void EnemyLayer::addEnemy(){
	schedule(schedule_selector(EnemyLayer::initEnemy),this->dt,kRepeatForever,0);
}
 
