#pragma once
#include"cocos2d.h"
USING_NS_CC;
class BulletLayer : public cocos2d::Layer
{
public:
	BulletLayer();
	~BulletLayer();
	CREATE_FUNC(BulletLayer);

	SpriteBatchNode* bulletBatchNode;
	SpriteBatchNode* blueBulletBatchNode;

	bool init();
	void addBullet(float dt);
	void addBlueBullet(float dt);
	Vector<Sprite*> m_pAllBullet;
	void bulletMoveFinished(Node* pSender);
	void startShoot(float delay);
	void startBlueShoot(float delay);
	void stopShoot();
	void stopBlue(float delay);
	void stopBlueShoot();
	void removeBullet(Sprite* bullet);
	void bulletMove(Sprite* bullet);
	
};

