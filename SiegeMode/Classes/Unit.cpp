#include "pch.h"
#include "Unit.h"

bool Unit::init()
{
	/*
	* 부모 클래스의 init()도 예의상 호출해준다.
	*/
	if (!this->Actor::init())
		return false;

	_cursor = Actor::create();
	_cursor->initWithSpriteFrameName("unitSelector1.png");
	this->addChild(_cursor);
	_cursor->setPosition(this->getContentSize());
	_cursor->setVisible(false);

	return true;
}

bool Unit::touchCallback(Touch* touch, Event* event)
{
	if (this->Actor::touchCallback(touch, event))
	{
		if (_selected)
		{
			_cursor->setVisible(false);
			_selected = false;
			return true;
		}
		//처음 선택하는 경우
		_cursor->setVisible(true);
		_selected = true;
		return true;
	}


	//다른 곳을 눌렀을 경우
	if (_selected)
	{
		Point pos = event->getCurrentTarget()->convertToNodeSpace(touch->getLocation());
		this->stopAllActions();
		this->runAction(MoveTo::create(1.f, touch->getLocation()));
	}

}
