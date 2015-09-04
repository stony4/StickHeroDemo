#include "GameOver.h"
#include "WelcomeScene.h"
USING_NS_CC;

bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto winSize = Director::getInstance()->getVisibleSize();

	auto OverBg = Sprite::create("scoreBg.png");
	OverBg->setScale(4);
	OverBg->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(OverBg);
	auto gameover = Label::createWithSystemFont("GameOver", "Î¢ÈíÑÅºÚ", 96);
	gameover->setAnchorPoint(Vec2(0.5, 0.5));
	gameover->setPosition(Vec2(winSize.width / 2 + 100, winSize.height / 2));
	this->addChild(gameover);


	/*auto welcomeScene = Scene::create();
	auto welcomeLayer = WelcomeScene::create();
	welcomeScene->addChild(welcomeLayer);
	Director::getInstance()->replaceScene(TransitionFade::create(2.0, welcomeScene));*/
	return true;
}