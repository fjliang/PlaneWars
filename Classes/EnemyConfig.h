#pragma once
#include<vector>
using std::string;
using std::vector;
class EnemyConfig
{

private:
	EnemyConfig();
	static EnemyConfig* enemyConfig;
public:
	
	~EnemyConfig();
	static EnemyConfig* getInstance(){
		if (NULL==enemyConfig){
			enemyConfig = new EnemyConfig();
		}
		return enemyConfig;
	};

	vector<string> vector_enemy1;
	vector<string> vector_enemy2;
	vector<string> vector_enemy3;



};

