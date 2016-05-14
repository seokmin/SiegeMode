#include "pch.h"
#include "BattleScene.h"
#include "UnitManager.h"
#include "SimpleAudioEngine.h"
#include "SummonButton.h"

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
	this->addChild(backgroundSpr,ZORDER_BACKGROUND);
	backgroundSpr->getTexture()->setAliasTexParameters();

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist");

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


//  	auto rt = RenderTexture::create(640, 400);
//  	BlendFunc blend;
//  	blend.src = GL_ONE_MINUS_SRC_ALPHA;
//  	blend.dst = GL_ONE_MINUS_SRC_COLOR;
//  	testUnit->setBlendFunc(blend);
//  	rt->beginWithClear(0, 0, 0, 0);
//  		testUnit->visit();
//  	rt->end();
//  	addChild(rt);
	
// 	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
// 
// 
// 	auto testListener = EventListenerTouchOneByOne::create();
// 	testListener->setSwallowTouches(true);
// 	testListener->onTouchBegan = CC_CALLBACK_2(BattleScene::onSprTouchBegan, this);
// 	dispatcher->addEventListenerWithSceneGraphPriority(testListener, this);

	auto btn = SummonButton::create(Vec2(800, 75), "swordman");
	addChild(btn);
	auto btn2 = SummonButton::create(Vec2(960, 75), "bowman");
	addChild(btn2);


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

bool BattleScene::onSprTouchBegan(Touch* touch, Event* event)
{
	static bool isRed = true;
	auto target = event->getCurrentTarget();
	Point pos = target->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 180, this->getContentSize().width, 200);
	if (rect.containsPoint(pos))
	{
		UnitManager::getInstance()->summonUnit("swordman", pos, isRed ? PLAYER_RED : PLAYER_BLUE);
		isRed = !isRed;
	}
	return false;
}

/*
bool BattleScene::onMouseTouchBegan(EventMouse* event)
{
	Point pos = event->getLocationInView();
	Rect rect = Rect(0, 180, this->getContentSize().width, 200);
	if (rect.containsPoint(pos))
	{
		static PLAYER_KIND currentPlayer = PLAYER_RED;
		if (event->getMouseButton() == 0)
			currentPlayer = PLAYER_RED;
		else if (event->getMouseButton() == 1)
			currentPlayer = PLAYER_BLUE;
		else
		{
			UnitManager::getInstance()->summonUnit("bowman", pos, currentPlayer);
			return false;
		}
		UnitManager::getInstance()->summonUnit("swordman", pos, currentPlayer);
	}

	return false;
}
*/

void BattleScene::update(float delta)
{

}
