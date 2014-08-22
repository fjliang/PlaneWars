#pragma once
#include"cocos2d.h"
#include"Enemy.h"
#include"EnemyConfig.h"
USING_NS_CC;
class EnemyLayer :public cocos2d::Layer
{
public:
	EnemyLayer();
	EnemyLayer(std::string enemyPng, int enemyLife, float dt);
	~EnemyLayer();
	CREATE_FUNC(EnemyLayer);
	Vector<Enemy*>  m_pAllEnemy;
	static const int maxLIFE1 = 1;
	static const int maxLIFE2 = 3;
	static const int maxLIFE3 = 5;
	EnemyConfig* enemyConfig;
	Sprite* enemyPlane;
	int enemyLife;
	std::string enemyPng;
	float dt;
	//SpriteBatchNode* pSpriteBatchNode;
	//µÐ»ú±¬Õ¨
	void enemyBlowup(Enemy* enemy);
	void removeEnemy(Enemy* enemy);
	void removeAllEnemy();
	void enemyMoveFinished(Enemy* enemy);
	void initEnemy(float dt);
	void addEnemy();
	
};

