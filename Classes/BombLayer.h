#pragma once
#include"cocos2d.h"
#include"GameConfig.h"
using std::string;
USING_NS_CC;
class BombLayer : public Layer
{
public:
	BombLayer();
	~BombLayer();
	CREATE_FUNC(BombLayer);
	bool init();
	static string setBomb(int number);
	int getBobm();
	void bobmUp(Ref* pSender);
private:
	int bombNumber;
	Label* number;
	//Sprite*  bomb;

};

