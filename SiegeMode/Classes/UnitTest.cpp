#include "pch.h"
#include "UnitTest.h"

bool UnitTest::init()
{
	/*
	* 부모 클래스의 init()도 예의상 호출해준다.
	*/
	if (!this->Unit::init())
		return false;


	this->initWithSpriteFrameName("swordman_walk_1.png");
	this->getTexture()->setAliasTexParameters();
	this->setAnchorPoint(Vec2(21.f / 28.f, 3.f / 28.f));
	auto asdf = this->getAnchorPoint();
	this->setToAlias();
	this->setCursor();
	return true;
}