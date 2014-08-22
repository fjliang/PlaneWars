#pragma once
#include"cocos2d.h"
USING_NS_CC; 
class EnemyConfig
{
public:
	EnemyConfig();
	~EnemyConfig();
	static EnemyConfig* getInstance();
	static Vector<std::string> vector_enemy1;
	static Vector<std::string> vector_enemy2;
	static Vector<std::string> vector_enemy3;

private:
	EnemyConfig* enemyConfig;

};


