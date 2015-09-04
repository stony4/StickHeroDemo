#include "Hero.h"
USING_NS_CC;

void Hero::init()
{
	heroSprite = Sprite::create("hero1.png");
	heroSprite->setAnchorPoint(Vec2(0.5, 0));
}

Sprite* Hero::getHeroSprite()
{
	return heroSprite;
}

void Hero::heroStay()
{
	Vector<SpriteFrame*> StayFrame;
	for (int i = 1; i < 6; i++)
	{
		char PngName[260] ;
		sprintf(PngName, "anim1/stay%d.png", i);
		StayFrame.pushBack(SpriteFrame::create(PngName, Rect(0, 0, 54, 58)));
	}
	auto stayAnimation = Animation::createWithSpriteFrames(StayFrame, 0.1);
	stayAnimation->setRestoreOriginalFrame(false);
	stayAnimation->setLoops(10000);
	auto stayAnimate = Animate::create(stayAnimation);
	heroSprite->runAction(stayAnimate);

}

void Hero::heroWalk()
{
	Vector<SpriteFrame*> WalkFrame;
	for (int i = 1; i < 6; i++)
	{
		char PngName[260];
		sprintf(PngName, "anim1/walk%d.png", i);
		WalkFrame.pushBack(SpriteFrame::create(PngName, Rect(0, 0, 54, 58)));
	}
	auto walkAnimation = Animation::createWithSpriteFrames(WalkFrame, 0.1);
	walkAnimation->setRestoreOriginalFrame(false);
	walkAnimation->setLoops(10000);
	auto walkAnimate = Animate::create(walkAnimation);
	heroSprite->runAction(walkAnimate);
}

void Hero::setPosition(Vec2 pos)
{
	heroSprite->setPosition(pos);
}