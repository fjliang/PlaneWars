#include "Enemy.h"


Enemy::Enemy()
{
	m_sprite = NULL;
	m_life = 0;

}
Enemy::~Enemy()
{
}
Enemy* Enemy::create(){
	Enemy* pRet = new Enemy();
	pRet->autorelease();
	return pRet;
}

void Enemy::bindSprite(Sprite* sprite, int life){
	m_sprite = sprite;
	m_life = life;
}
Sprite* Enemy::getEnemy(){
	return m_sprite;
}
int Enemy::getLife(){
	return m_life;
}
void Enemy::loseLife(){
	m_life--;
}
Rect Enemy::getBoundingBox(){
	Rect rect= m_sprite->boundingBox();
	Point pos=this->convertToWorldSpace(rect.origin);
	return   Rect(pos.x, pos.y, rect.size.width, rect.size.height);
	
}