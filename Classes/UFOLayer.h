#pragma once
#include"cocos2d.h"
#include"GameConfig.h"
using std::string;
USING_NS_CC;
class UFOLayer :public Layer
{
public:
	UFOLayer();
	UFOLayer(string ufoPng);
	~UFOLayer();
	CREATE_FUNC(UFOLayer);
	bool init();
	void addUFO(float dt);
	void removeUFO(Sprite* ufo);
	void startUFO(float dt);
	string ufoPng;
	float dt;
	float interval;
	SpriteBatchNode* spriteBatchNode;
	Vector<Sprite*> vector_ufo;
	void startUFO();
	

};

