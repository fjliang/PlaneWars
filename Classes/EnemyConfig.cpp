#include "EnemyConfig.h"


EnemyConfig::EnemyConfig()
{
	vector_enemy1.pushBack("enemy1_down1.png");
	vector_enemy1.pushBack("enemy1_down2.png");
	vector_enemy1.pushBack("enemy1_down3.png");
	vector_enemy1.pushBack("enemy1_down4.png");

	vector_enemy2.pushBack("enemy2_down1.png");
	vector_enemy2.pushBack("enemy2_down2.png");
	vector_enemy2.pushBack("enemy2_down3.png");
	vector_enemy2.pushBack("enemy2_down4.png");

	vector_enemy3.pushBack("enemy3_down1.png");
	vector_enemy3.pushBack("enemy3_down2.png");
	vector_enemy3.pushBack("enemy3_down3.png");
	vector_enemy3.pushBack("enemy3_down4.png");
	vector_enemy3.pushBack("enemy3_down5.png");
	vector_enemy3.pushBack("enemy3_down6.png");

}

EnemyConfig::~EnemyConfig()
{
}
EnemyConfig* EnemyConfig::getInstance(){
	if (enemyConfig== NULL){
		enemyConfig = new EnemyConfig();
	}
	return enemyConfig;
}