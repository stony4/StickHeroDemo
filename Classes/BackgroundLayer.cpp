#include "BackgroundLayer.h"

USING_NS_CC;

bool BackgroundLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	winSize = Director::getInstance()->getVisibleSize();
	isStart = false;
	//产生随机数种子
	srand((unsigned)time(NULL));
	int randNum = rand() % 5;
	AddBG(randNum);
	//游戏名称《StickHero》
	auto GameName = Sprite::create("uires_1.png");
	GameName->setPosition(Vec2(winSize.width / 2, winSize.height / 5 * 4));
	GameName->setName("GameName");
	this->addChild(GameName);
	//开始
	StartSprite = MenuItemSprite::create(Sprite::create("uires_2.png"), Sprite::create("uires_2.png"), NULL,this, menu_selector(BackgroundLayer::StartGame));
	StartSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	auto StartMoveUp = MoveTo::create(2, Vec2(winSize.width / 2, winSize.height / 2 + 10));
	auto StartMoveDown = MoveTo::create(2, Vec2(winSize.width / 2, winSize.height / 2 - 10));
	auto seqAction = Sequence::create(StartMoveUp, StartMoveDown, NULL);
	auto repAction = RepeatForever::create(seqAction);
	StartSprite->runAction(repAction);
	menu = Menu::create(StartSprite, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	//台阶
	StageSprite[0] = Sprite::create("stage1.png");
	StageSprite[0]->setScaleX(20);
	StageSprite[0]->setPosition(Vec2(winSize.width / 2, 0));
	this->addChild(StageSprite[0]);

	for (int i = 1; i < 3; i++)
	{
		StageSprite[i] = Sprite::create("stage1.png");
	}
	for (int i = 1; i < 3; i++)
	{
		StageSprite[i]->setPosition(Vec2(winSize.width + StageSprite[i]->getContentSize().width / 2, StageSprite[i]->getContentSize().height / 2));
	}
	for (int i = 1; i < 3; i++)
	{
		this->addChild(StageSprite[i]);
	}
	//Hero
	hero.init();
	hero.setPosition(Vec2(winSize.width / 2, StageSprite[0]->getContentSize().height / 2));
	this->addChild(hero.getHeroSprite());
	hero.heroStay();
	//棍子
	stick = Sprite::create("stick1.png");
	stick->setAnchorPoint(Vec2(1, 0));
	stick->setPosition(Vec2(-stick->getContentSize().width, StageSprite[0]->getContentSize().height));
	this->addChild(stick);


	//触摸
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [&](Touch* touch, Event* event)
	{
		if (isStart)
		{
			AddStick();
		}
		return true;
	};
	listener->onTouchEnded = [&](Touch* touch, Event* event)
	{

		if (isStart)
		{
			getStickLenght();
			StickRotateAndWalk();
			
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		
	return true;
}

void BackgroundLayer::AddBG(int prand)
{
	switch (prand)
	{
	case 0:
		background_1 = Sprite::create("bg/bg1.jpg");
		break;
	case 1:
		background_1 = Sprite::create("bg/bg2.jpg");
		break;
	case 2:
		background_1 = Sprite::create("bg/bg3.jpg");
		break;
	case 3:
		background_1 = Sprite::create("bg/bg4.jpg");
		break;
	case 4:
		background_1 = Sprite::create("bg/bg5.jpg");
		break;
	default:
		break;
	}

	background_1->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
	this->addChild(background_1);
}

void BackgroundLayer::StartGame(Ref* psend)
{
	isStart = true;
	this->removeChild(menu);
	this->removeChildByName("GameName");
	auto heroMove_1 = MoveTo::create(1, Vec2(StageSprite[0]->getContentSize().width / 2 * 20, StageSprite[0]->getContentSize().height));
	auto stageMove_1 = MoveTo::create(1, Vec2(StageSprite[0]->getContentSize().width / 2 * 20, StageSprite[0]->getContentSize().height / 2));
	StageSprite[0]->runAction(stageMove_1);
	hero.getHeroSprite()->runAction(heroMove_1);
	AddStage();
}

void BackgroundLayer::AddStage()
{
	if (StageNum +1<=2)
	{
		StageNum += 1;
	}
	else
	{
		StageNum = 0;
	}
	StageSprite[StageNum]->setScaleX(10 + CCRANDOM_0_1() * 40);
	auto stageMove = MoveTo::create(1, Vec2(150 + winSize.width / 2, StageSprite[StageNum]->getContentSize().height / 2));
	StageSprite[StageNum]->runAction(stageMove);
	//从左向右，第一块Fir，第二块Mid，第三块Last
	Stage_Mid = StageNum;
	Stage_Fir = Stage_Mid == 0 ? 2 : Stage_Mid - 1;
	Stage_Last = Stage_Mid == 2 ? 0 : Stage_Mid + 1;
}

void BackgroundLayer::MoveStage(float)
{
	StageSprite[Stage_Fir]->setPosition(Vec2(winSize.width + StageSprite[Stage_Fir]->getContentSize().width*StageSprite[Stage_Fir]->getScaleX() / 2, StageSprite[Stage_Fir]->getContentSize().height / 2));
	auto Stage_Mid_Move = MoveTo::create(1, Vec2(StageSprite[Stage_Mid]->getContentSize().width*StageSprite[Stage_Mid]->getScaleX() / 2, StageSprite[Stage_Mid]->getContentSize().height / 2));
	auto hero_Move = MoveTo::create(1, Vec2(StageSprite[Stage_Mid]->getContentSize().width*StageSprite[Stage_Mid]->getScaleX() / 2, StageSprite[Stage_Mid]->getContentSize().height));
	StageSprite[Stage_Mid]->runAction(Stage_Mid_Move);
	//角色移动
	hero.getHeroSprite()->runAction(hero_Move);
	//重置棍子
	ResetStick();
	AddStage();
}

void BackgroundLayer::AddStick()
{
	stick->setPosition(Vec2(StageSprite[Stage_Fir]->getContentSize().width*StageSprite[Stage_Fir]->getScaleX(), StageSprite[0]->getContentSize().height));

	this->schedule(schedule_selector(BackgroundLayer::StickAddLenght));
}

void BackgroundLayer::StickAddLenght(float)
{
	stick->setScaleY(stick->getScaleY() + 1);
}

void BackgroundLayer::ResetStick()
{
	stick->setRotation(0);
	stick->setPosition(Vec2(-stick->getContentSize().width, StageSprite[0]->getContentSize().height));
	stick->setScaleY(0);
}

void BackgroundLayer::getStickLenght()
{
	stickLenght = stick->getContentSize().height*stick->getScaleY();
	this->unschedule(schedule_selector(BackgroundLayer::StickAddLenght));
}

void BackgroundLayer::StickRotateAndWalk()
{
	Lenght_min = abs(StageSprite[Stage_Mid]->getPositionX() - StageSprite[Stage_Fir]->getPositionX()) - StageSprite[Stage_Mid]->getContentSize().width*StageSprite[Stage_Mid]->getScaleX() / 2 - StageSprite[Stage_Fir]->getContentSize().width*StageSprite[Stage_Fir]->getScaleX() / 2;
	Lenght_max = Lenght_min + StageSprite[Stage_Mid]->getContentSize().width*StageSprite[Stage_Mid]->getScaleX();
	if (Lenght_min<stickLenght && stickLenght<Lenght_max)
	{
		//棍子旋转
		auto stick_Rotate = RotateTo::create(2, 90);
		stick->runAction(stick_Rotate);
		//人物行走
		this->scheduleOnce(schedule_selector(BackgroundLayer::PlayerWalk),2.0);
		
	}
	else if (stickLenght<Lenght_min)
	{
		auto stick_RotateDown = RotateTo::create(2, 180);
		stick->runAction(stick_RotateDown);
		this->schedule(schedule_selector(BackgroundLayer::Over), 1.0);
	}

}
void BackgroundLayer::PlayerWalk(float)
{
	auto heroWalkAction = MoveTo::create(2, Vec2(StageSprite[Stage_Mid]->getPosition().x, StageSprite[Stage_Mid]->getContentSize().height));
	hero.heroWalk();
	hero.getHeroSprite()->runAction(heroWalkAction);

	this->scheduleOnce(schedule_selector(BackgroundLayer::MoveStage), 2.0);
}

void BackgroundLayer::Over(float)
{
	over = GameOver::create();
	this->addChild(over,100);

	
}