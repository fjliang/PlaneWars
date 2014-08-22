#pragma once
#include"cocos2d.h"
USING_NS_CC;
class Enemy :public cocos2d::Sprite
{
public:
	Enemy();
	~Enemy();
	int m_life;
	Sprite* m_sprite;
	static Enemy* create();
	virtual void bindSprite(Sprite* sprite, int life);
	virtual Sprite* getEnemy();
	int getLife();
	void loseLife();
	Rect getBoundingBox();
};

