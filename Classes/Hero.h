#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Hero
{
public:
	virtual void init();
	//��ȡ����
	Sprite* getHeroSprite();
	//���Ƕ���
	void heroStay();
	void heroWalk();
	//
	void setPosition(Vec2);
private:
	Sprite* heroSprite;
};