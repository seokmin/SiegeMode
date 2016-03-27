#include "pch.h"
#include "HelloWorldScene.h"
#include "UnitTest.h"
#include "InputManager.h"

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
    if ( !LayerColor::initWithColor(ccc4(255,255,255,255)) )
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
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("test.plist");



    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	auto testUnit = UnitTest::create();
	testUnit->setPosition(visibleSize.width/2, visibleSize.height/2);
	testUnit->initWithSpriteFrameName("swordman_walk_1.png");
	this->addChild(testUnit);
	testUnit->getTexture()->setAliasTexParameters();
	testUnit->setScale(3.0f);
	auto testUnit2 = UnitTest::create();
	testUnit2->setPosition(visibleSize.width / 2+100, visibleSize.height / 2);
	testUnit2->initWithSpriteFrameName("swordman_walk_1.png");
	this->addChild(testUnit2);
	testUnit2->getTexture()->setAliasTexParameters();
	testUnit2->setScale(3.0f);
	auto testUnit3 = UnitTest::create();
	testUnit3->setPosition(visibleSize.width / 2- 100,visibleSize.height / 2);
	testUnit3->initWithSpriteFrameName("swordman_walk_1.png");
	this->addChild(testUnit3);
	testUnit3->getTexture()->setAliasTexParameters();
	testUnit3->setScale(3.0f);

	InputManager::getInstance()->addTouchEvent(testUnit);
	InputManager::getInstance()->addTouchEvent(testUnit2);
	InputManager::getInstance()->addTouchEvent(testUnit3);
// 
// 	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
// 	auto testListener = EventListenerTouchOneByOne::create();
// 	testListener->setSwallowTouches(true);
// 	testListener->onTouchBegan = CC_CALLBACK_2(BattleScene::onSprTouchBegan, this);
// 	dispatcher->addEventListenerWithSceneGraphPriority(testListener, testUnit);

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
	auto target = event->getCurrentTarget();
	Point pos = target->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
	//if(rect.containsPoint(pos))
		target->setPosition(0, 0);
	return false;
}