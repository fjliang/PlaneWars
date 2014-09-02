#pragma once
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "UFOLayer.h"
#include "ControlLayer.h"
#include "GameOverLayer.h"
#include "GameOverScene.h"

USING_NS_CC; 
class GameLayer : public cocos2d::Layer
{
public:
	GameLayer();
	~GameLayer();
	CREATE_FUNC(GameLayer);
	bool init();
	void initBomb();
	void backgroundMove(float dt);
	static int bombNumber;
	PlaneLayer* _planeLayer; 
	BulletLayer* _bulletLayer;
	EnemyLayer* _enemyLayer1;
	EnemyLayer* _enemyLayer2;
	EnemyLayer* _enemyLayer3;
	ControlLayer* control;
	void collisionDetection();
	void update(float dt);
	void removePlane(float dt);
	string setBomb(int number);
	void bobmUp(Ref* pSender);
};

