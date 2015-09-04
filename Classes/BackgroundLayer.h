#pragma once
#include "cocos2d.h"
#include "Hero.h"
#include "GameOver.h"
#include "WelcomeScene.h"

USING_NS_CC;
class BackgroundLayer :public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(BackgroundLayer);

	//添加背景图
	void AddBG(int	);
	//开始按键
	void StartGame(cocos2d::Ref* ref);
	//台阶
	void AddStage();
	void MoveStage(float);
	//棍子
	void AddStick();
	void StickAddLenght(float);
	void getStickLenght();
	void StickRotateAndWalk();
	void ResetStick();	
	//角色
	void PlayerWalk(float);
	//
	void Over(float);

private:
	int Stage_Mid;
	int Stage_Fir;
	int Stage_Last;
	//游戏状态
	bool isStart;
	//背景画面
	cocos2d::Sprite* background_1;
	cocos2d::Sprite* background_2;
	cocos2d::Size winSize;
	//台阶精灵
	cocos2d::Sprite* StageSprite[3];
	int StageNum;
	MenuItemSprite* StartSprite;
	Menu* menu;
	//主角Hero
	Hero hero;
	//棍子
	Sprite* stick;
	float stickLenght;

	int Lenght_min;
	int Lenght_max;
	//
	GameOver* over;
	

};