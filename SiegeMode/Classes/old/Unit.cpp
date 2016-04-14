#include "pch.h"
#include "Unit.h"

bool Unit::init()
{
	/*
	* 부모 클래스의 init()도 예의상 호출해준다.
	*/
	if (!this->Actor::init())
		return false;
	this->setScale(2.f);

	return true;
}

bool Unit::touchCallback(Touch* touch, Event* event)
{
	this->refreshStroke();
	return true;

}

cocos2d::Action* Unit::getActionItem(const std::string& actionName)
{
	return this->_actionList[actionName];
}
