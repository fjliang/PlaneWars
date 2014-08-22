#pragma once
#include"cocos2d.h"
USING_NS_CC;
class BulletLayer : public cocos2d::Layer
{
public:
	BulletLayer();
	~BulletLayer();
	CREATE_FUNC(BulletLayer);
	bool init();
	void addBullet(float dt);
	Vector<Sprite*> m_pAllBullet;
	void bulletMoveFinished(Node* pSender);
	void startShoot(float delay);
	void stopShoot();
	void removeBullet(Sprite* bullet);
	void bulletMove(Sprite* bullet);
	
};

