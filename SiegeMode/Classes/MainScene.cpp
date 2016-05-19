#include "pch.h"
#include "BattleScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "definition.h"

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
	this->setName("MainScene");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	CCSprite * background = CCSprite::create("SpriteSource/background/title.png");
	background->setScaleX((visibleSize.width / background->getContentSize().width) * 1);
	background->setScaleY((visibleSize.height / background->getContentSize().height) * 1);
	background->setAnchorPoint(Point(0,0));
	this->addChild(background);

	Sprite* start_btn = Sprite::create("SpriteSource/UI/start_button.png");
	Sprite* start_btn_clicked = Sprite::create("SpriteSource/UI/start_button_clicked.png");

	Sprite* exit_btn = Sprite::create("SpriteSource/UI/exit_button.png");
	Sprite* exit_btn_clicked = Sprite::create("SpriteSource/UI/exit_button_clicked.png");

	MenuItemSprite* menu_play = MenuItemSprite::create(start_btn, start_btn_clicked, CC_CALLBACK_1(MainScene::MenuClickCallback, this));
	MenuItemSprite* menu_exit = MenuItemSprite::create(exit_btn, exit_btn_clicked, CC_CALLBACK_1(MainScene::MenuCloseCallback, this));
// 
// 	Sprite* credit_btn = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_CREDIT);
// 	Sprite* credit_btn_clicked = Sprite::createWithSpriteFrameName(FILENAME_IMG_BUTTON_CREDIT_CLICKED);
// 	MenuItemSprite* menu_credit = MenuItemSprite::create(credit_btn, credit_btn_clicked, CC_CALLBACK_0(MainScene::ShowCredit, this));

	auto mainMenu = Menu::create(menu_play, menu_exit, /*menu_credit,*/ nullptr);
	menu_play->setPosition(visibleSize.width/2, visibleSize.height/2-100);
	menu_exit->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 200);
/*	menu_credit->setPosition(visibleSize.width * 7 / 8, visibleSize.height * 1 / 8);*/

	mainMenu->setPosition(Vec2::ZERO);
	this->addChild(mainMenu);

//	Keyboard Event

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Sound/10-time-2-kill.mp3",true);

	return true;
}

void MainScene::MenuClickCallback(cocos2d::Ref* pSender)
{
	auto gameScene = BattleScene::createScene();
	Director::getInstance()->pushScene(gameScene);
}

void MainScene::MenuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
