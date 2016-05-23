#include "pch.h"
#include "BattleScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "definition.h"
#include "AnimationManager.h"

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	setName("MainScene");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	// 배경
	auto * background = Sprite::create("SpriteSource/background/title.png");
	background->setScaleX((visibleSize.width / background->getContentSize().width) * 1);
	background->setScaleY((visibleSize.height / background->getContentSize().height) * 1);
	background->setAnchorPoint(Point(0, 0));
	addChild(background);



	// 시작, 종료 메뉴
	Sprite* start_btn = Sprite::create("SpriteSource/UI/start_button.png");
	Sprite* start_btn_clicked = Sprite::create("SpriteSource/UI/start_button_clicked.png");
	Sprite* exit_btn = Sprite::create("SpriteSource/UI/exit_button.png");
	Sprite* exit_btn_clicked = Sprite::create("SpriteSource/UI/exit_button_clicked.png");

	MenuItemSprite* menu_play = MenuItemSprite::create(start_btn, start_btn_clicked, CC_CALLBACK_1(MainScene::MenuClickCallback, this));
	MenuItemSprite* menu_exit = MenuItemSprite::create(exit_btn, exit_btn_clicked, CC_CALLBACK_1(MainScene::MenuCloseCallback, this));

	auto mainMenu = Menu::create(menu_play, menu_exit, nullptr);
	menu_play->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
	menu_exit->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);

	mainMenu->setPosition(Vec2::ZERO);
	addChild(mainMenu);



	// 사운드 프리로드
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/bow_release.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/hit.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/stab.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/10-time-2-kill.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/32-army-of-drums.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/32-army-of-drums.mp3", true);

	AnimationManager::getInstance();
	return true;
}

void MainScene::MenuClickCallback(cocos2d::Ref* pSender)
{
	auto gameScene = BattleScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}

void MainScene::MenuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}