#include "pch.h"
#include "Unit.h"

bool Unit::init()
{
	/*
	* 부모 클래스의 init()도 예의상 호출해준다.
	*/
	if (!this->Actor::init())
		return false;
	this->setScale(3.f);

	return true;
}

bool Unit::touchCallback(Touch* touch, Event* event)
{
	if (this->Actor::touchCallback(touch, event))
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
	}

}

cocos2d::Action* Unit::getActionItem(const std::string& actionName)
{
	return this->_actionList[actionName];
}

void Unit::setCursor()
{
	Vec2 anchorP = this->getAnchorPoint();
	Size tempSize = this->getContentSize();

	_cursorDown = Actor::create();
	_cursorUp = Actor::create();
	_cursorDown->initWithSpriteFrameName("unitSelector1_d.png");
	_cursorUp->initWithSpriteFrameName("unitSelector1_u.png");
	_cursorUp->setPosition(Vec2(anchorP.x*tempSize.width, anchorP.y*tempSize.height));
	_cursorDown->setPosition(_cursorUp->getPosition() - Vec2(0,5));
	_cursorDown->setVisible(false);
	_cursorUp->setVisible(false);
	_cursorUp->setZOrder(this->getZOrder() - 1);
	_cursorDown->setZOrder(this->getZOrder() + 1);

	this->addChild(_cursorDown);
	this->addChild(_cursorUp);
}

void Unit::addActionItem(const std::string actionName, Action* action)
{
	this->_actionList.insert_or_assign(actionName, action);
}
