#pragma once
#include<vector>
using std::string;
using std::vector;
class GameConfig
{

private:
	GameConfig();
	static GameConfig* gameConfig;
public:
	
	~GameConfig();
	static GameConfig* getInstance(){
		if (NULL==gameConfig){
			gameConfig = new GameConfig();
		}
		return gameConfig;
	};

	vector<string> vector_enemy1;
	vector<string> vector_enemy2;
	vector<string> vector_enemy3;

	static bool GAME_OVER;
	static const int maxLIFE1 = 1;
	static const int maxLIFE2 = 3;
	static const int maxLIFE3 = 5;

	static const int ENEMY1_DT = 1;
	static const int ENEMY2_DT = 3;
	static const int ENEMY3_DT = 5;

	static const int ENEMY_MIN_SPEED = 30 ;
	static const int ENEMY_MAX_SPEED = 5 ;



};

