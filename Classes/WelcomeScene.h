#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"

class WelcomeScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(WelcomeScene);

private:
	BackgroundLayer* BG_layer;
};