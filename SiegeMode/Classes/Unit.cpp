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

	/*if (this->Actor::touchCallback(touch, event))
	{
		if (_selected)
		{
			_cursorUp->setVisible(false);
			_cursorDown->setVisible(false);
			_selected = false;
			return true;
		}
		//처음 선택하는 경우
		_cursorUp->setVisible(true);
		_cursorDown->setVisible(true);
		_selected = true;
		return true;
	}


	//다른 곳을 눌렀을 경우
	if (_selected)
	{
		Point pos = event->getCurrentTarget()->convertToNodeSpace(touch->getLocation());
		this->stopAllActions();
		this->runAction(MoveTo::create(1.f, touch->getLocation()));
	}*/
	return true;

}

cocos2d::Action* Unit::getActionItem(const std::string& actionName)
{
	return this->_actionList[actionName];
}
