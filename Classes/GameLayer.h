#pragma once
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
USING_NS_CC; 
class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();
	~GameLayer();
	CREATE_FUNC(GameLayer);
	bool init();
	void backgroundMove(float dt);
	PlaneLayer* _planeLayer; 
	BulletLayer* _bulletLayer;
	EnemyLayer* _enemyLayer1;
	EnemyLayer* _enemyLayer2;
	EnemyLayer* _enemyLayer3;
	void collisionDetection();
	void update(float dt);
};
