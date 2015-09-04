#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Hero
{
public:
	virtual void init();
	//获取精灵
	Sprite* getHeroSprite();
	//主角动作
	void heroStay();
	void heroWalk();
	//
	void setPosition(Vec2);
private:
	Sprite* heroSprite;
};