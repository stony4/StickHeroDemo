#include "WelcomeScene.h"
USING_NS_CC;

Scene* WelcomeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();
	scene->addChild(layer);
	return scene;
}

bool WelcomeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//ÓÎÏ·±³¾°Background
	BG_layer = BackgroundLayer::create();
	this->addChild(BG_layer);
	
	
	return true;
}