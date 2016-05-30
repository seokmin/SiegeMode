#include "pch.h"
#include "BattleScene.h"
#include "UnitManager.h"
#include "SimpleAudioEngine.h"
#include "SummonButton.h"
#include <array>
#include "MainScene.h"

Scene* BattleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene::create();
	scene->addChild(layer);

	return scene;
}

bool BattleScene::init()
{
	if (!LayerColor::initWithColor(Color4B(120, 120, 120, 120)))
		return false;

	// --배경 이미지------------------------------------------
	auto backgroundSpr = Sprite::create("SpriteSource/background/backgroundHigher.png");
	backgroundSpr->setAnchorPoint(Vec2(0, 0));
	addChild(backgroundSpr,DEF::ZORDER_BACKGROUND);
	backgroundSpr->getTexture()->setAliasTexParameters();
	addChild(UnitManager::getInstance()->getUnitList(),2);
	// --배경 음악--------------------------------------------
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/10-time-2-kill.mp3", true);
	// --레이블 설정------------------------------------------
	auto label = Label::createWithTTF("SiegeMode! - prototype", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(DEF::SCREEN_WIDTH/ 2,DEF::SCREEN_HEIGHT - label->getContentSize().height));
	addChild(label, 3);

	// 게임 종료 버튼-----------------------------------------
	auto closeItem = MenuItemImage::create(
		"SpriteSource/UI/exit_button.png",
		"SpriteSource/UI/exit_button_clicked.png",
		CC_CALLBACK_1(BattleScene::menuCloseCallback, this));
	closeItem->setScale(0.75f);
	closeItem->setPosition(Vec2(DEF::SCREEN_WIDTH - closeItem->getContentSize().width / 2,
		+ closeItem->getContentSize().height / 2));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	addChild(menu, 1);

	// --각 유닛들 소환 버튼----------------------------------
	auto btn = SummonButton::create(Vec2(640, 75), "swordman");
	addChild(btn);
	auto btn2 = SummonButton::create(Vec2(800, 75), "bowman");
	addChild(btn2);
	auto btn3 = SummonButton::create(Vec2(960, 75), "balistar");
	addChild(btn3);


	// --플래그맨 두기----------------------------------------
	UnitManager::getInstance()->summonUnit("flagman", Vec2(30, 250), DEF::PLAYER_RED);
	UnitManager::getInstance()->summonUnit("flagman", Vec2(DEF::SCREEN_WIDTH-30,250), DEF::PLAYER_BLUE);

	scheduleUpdate();
	return true;
}

// 게임 종료(메인화면으로 돌아감)
void BattleScene::menuCloseCallback(Ref* pSender)
{
	UnitManager::getInstance()->deleteInstance();
	auto newScene = MainScene::createScene();
	Director::getInstance()->replaceScene(newScene);
	Director::getInstance()->resume();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

// 매 프레임 호출
void BattleScene::update(float delta)
{
	// 급조한 유닛 웨이브
	static auto freqDelta = 0.f;
	static auto sumDelta = 0.f;
	static auto	frequency = 2.f;

	freqDelta += delta;
	sumDelta += delta;

	auto saturated_sin = sin(sumDelta * 20.f * 3.141592f);
	if (sumDelta >= frequency)
	{
		frequency = RandomHelper::random_real(3.25f + saturated_sin, 4.5f + saturated_sin);
		auto randY = RandomHelper::random_real(DEF::FIGHTING_ZONE.getMinY(), DEF::FIGHTING_ZONE.getMaxY());

		//랜덤으로 하나 고른다.
		static std::array<std::string,(size_t)2> names = {"swordman","bowman"};
		auto randIt =names.begin();
		std::advance(randIt, RandomHelper::random_int(0u, names.size() - 1));

		UnitManager::getInstance()->summonUnit(*randIt, Vec2(DEF::SCREEN_WIDTH,randY), DEF::PLAYER_BLUE);
		sumDelta = 0.f;
	}
	// 유닛웨이브 끝
}