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

};

