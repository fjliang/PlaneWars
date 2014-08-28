#include "GameConfig.h"

GameConfig* GameConfig::gameConfig = NULL;
bool GameConfig::GAME_OVER = false;
 
GameConfig::GameConfig()
{
	vector_enemy1.push_back("enemy1_down1.png");
	vector_enemy1.push_back("enemy1_down2.png");
	vector_enemy1.push_back("enemy1_down3.png");
	vector_enemy1.push_back("enemy1_down4.png");

	vector_enemy2.push_back("enemy2_down1.png");
	vector_enemy2.push_back("enemy2_down2.png");
	vector_enemy2.push_back("enemy2_down3.png");
	vector_enemy2.push_back("enemy2_down4.png");

	vector_enemy3.push_back("enemy3_down1.png");
	vector_enemy3.push_back("enemy3_down2.png");
	vector_enemy3.push_back("enemy3_down3.png");
	vector_enemy3.push_back("enemy3_down4.png");
	vector_enemy3.push_back("enemy3_down5.png");
	vector_enemy3.push_back("enemy3_down6.png");
}

GameConfig::~GameConfig()
{
}
