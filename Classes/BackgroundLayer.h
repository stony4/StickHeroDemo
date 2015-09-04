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

	//��ӱ���ͼ
	void AddBG(int	);
	//��ʼ����
	void StartGame(cocos2d::Ref* ref);
	//̨��
	void AddStage();
	void MoveStage(float);
	//����
	void AddStick();
	void StickAddLenght(float);
	void getStickLenght();
	void StickRotateAndWalk();
	void ResetStick();	
	//��ɫ
	void PlayerWalk(float);
	//
	void Over(float);

private:
	int Stage_Mid;
	int Stage_Fir;
	int Stage_Last;
	//��Ϸ״̬
	bool isStart;
	//��������
	cocos2d::Sprite* background_1;
	cocos2d::Sprite* background_2;
	cocos2d::Size winSize;
	//̨�׾���
	cocos2d::Sprite* StageSprite[3];
	int StageNum;
	MenuItemSprite* StartSprite;
	Menu* menu;
	//����Hero
	Hero hero;
	//����
	Sprite* stick;
	float stickLenght;

	int Lenght_min;
	int Lenght_max;
	//
	GameOver* over;
	

};