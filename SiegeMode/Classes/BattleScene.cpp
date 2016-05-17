#include "pch.h"
#include "BattleScene.h"
#include "UnitManager.h"
#include "SimpleAudioEngine.h"
#include "SummonButton.h"
#include <array>

Scene* BattleScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = BattleScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool BattleScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!LayerColor::initWithColor(Color4B(120, 120, 120, 120)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(BattleScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// set background image
	auto backgroundSpr = Sprite::create("SpriteSource/background/backgroundHigher.png");
	backgroundSpr->setAnchorPoint(Vec2(0, 0));
	this->addChild(backgroundSpr,DEF::ZORDER_BACKGROUND);
	backgroundSpr->getTexture()->setAliasTexParameters();

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/bow_release.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/hit.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/stab.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/10-time-2-kill.mp3", true);
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.7f);
	this->addChild(UnitManager::getInstance()->getUnitList(),2);
	auto label = Label::createWithTTF("SiegeMode! - prototype", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 3);


	auto btn = SummonButton::create(Vec2(800, 75), "swordman");
	addChild(btn);
	auto btn2 = SummonButton::create(Vec2(960, 75), "bowman");
	addChild(btn2);

	//플래그맨 두기.
	UnitManager::getInstance()->summonUnit("flagman", Vec2(30, 250), DEF::PLAYER_RED);
	UnitManager::getInstance()->summonUnit("flagman", Vec2(DEF::SCREEN_WIDTH-30,250), DEF::PLAYER_BLUE);

	UnitManager::getInstance()->summonUnit("bowman", Vec2(DEF::SCREEN_WIDTH - 200, 250), DEF::PLAYER_RED);

	this->scheduleUpdate();
	return true;
}


void BattleScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void BattleScene::update(float delta)
{
	static auto freqDelta = 0.f;
	static auto sumDelta = 0.f;
	static auto	frequency = 2.f;

	freqDelta += delta;
	sumDelta += delta;

	auto saturated_sin = sin(sumDelta * 20.f * 3.141592f);
	//if (saturated_sin < 0.f) saturated_sin = 0.f;
	if (sumDelta >= frequency)
	{
		frequency = RandomHelper::random_real(1.25f + saturated_sin, 4.f + saturated_sin);
		auto randY = RandomHelper::random_real(DEF::FIGHTING_ZONE.getMinY(), DEF::FIGHTING_ZONE.getMaxY());

		//랜덤으로 하나 고른다.
		static std::array<std::string,(size_t)2> names = {"swordman","bowman"};
		auto randIt =names.begin();
		std::advance(randIt, RandomHelper::random_int(0u, names.size() - 1));
		if (*randIt == "bowman")
		{
			randIt = names.begin();
			std::advance(randIt, RandomHelper::random_int(0u, names.size() - 1));
		}

		UnitManager::getInstance()->summonUnit(*randIt, Vec2(DEF::SCREEN_WIDTH,randY), DEF::PLAYER_BLUE);
		sumDelta = 0.f;
	}

}