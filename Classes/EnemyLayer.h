#pragma once
#include"cocos2d.h"
#include"Enemy.h"
#include"GameConfig.h"
USING_NS_CC;
class EnemyLayer :public cocos2d::Layer
{
public:
	EnemyLayer();
	EnemyLayer(std::string enemyPng, int enemyLife, float dt);
	~EnemyLayer();
	CREATE_FUNC(EnemyLayer);
	Vector<Enemy*>  m_pAllEnemy;
	GameConfig* gameConfig;
	Sprite* enemyPlane;
	int enemyLife;
	std::string enemyPng;
	float dt;
	SpriteBatchNode* pSpriteBatchNode;
	//µÐ»ú±¬Õ¨
	void enemyBlowup(Enemy* enemy);
	void removeEnemy(Enemy* enemy);
	void removeAllEnemy();
	void enemyMoveFinished(Enemy* enemy);
	void initEnemy(float dt);
	void addEnemy();
	Animation* getBlowupAnimation(Animation* animation,string enemyPng);
	
};

