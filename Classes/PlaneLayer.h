#pragma once
#include "cocos2d.h"
USING_NS_CC;
class PlaneLayer : public cocos2d::Layer
{
public:
	PlaneLayer();
	~PlaneLayer();
	CREATE_FUNC(PlaneLayer);
	static PlaneLayer *createPlane();
	virtual bool init();
	static PlaneLayer* sharedPlane;//提供sharedPlane全局指针
	const static int AIRPLANE = 111;
	static bool isAlive;
	void initTouchEvent();
	void moveTo(Point location);

};



