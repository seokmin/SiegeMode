#include "pch.h"
#include "SummonButton.h"
#include "UnitManager.h"

std::string SummonButton::_selectedUnitName = "";
bool SummonButton::_isRed = true;

SummonButton* SummonButton::create(Vec2 pos, std::string unitName)
{
	auto newInst = SummonButton::create();
	newInst->setPosition(pos);
	newInst->setGlobalZOrder(ZORDER_UI);

	auto newFrame = Sprite::create("SpriteSource/UI/unit_frame.png");
	auto newUnit = Sprite::create("SpriteSource/UI/" + unitName + ".png");

	newUnit->setLocalZOrder(newFrame->getLocalZOrder() + 1);
	newUnit->setGlobalZOrder(ZORDER_UI);
	newFrame->setGlobalZOrder(ZORDER_UI);
	newInst->addChild(newFrame);
	newInst->addChild(newUnit);
	newFrame->getTexture()->setAliasTexParameters();
	newUnit->getTexture()->setAliasTexParameters();

	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SummonButton::onSprTouchBegan, newInst);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, newInst);

	newInst->setFrame(newFrame);
	newInst->setUnit(newUnit);
	newInst->setAnchorPoint(Vec2(0.f,0.f));
	newInst->setUnitName(unitName);
	return newInst;
}

bool SummonButton::onSprTouchBegan(Touch* touch, Event* event)
{
	//소환체크

	if (_selectedUnitName != "")
	{

		Point pos = touch->getLocation();
		Rect rect = Rect(0, 180, getParent()->getContentSize().width, 200);
		if (rect.containsPoint(pos))
		{
			UnitManager::getInstance()->summonUnit(_selectedUnitName, pos, _isRed ? PLAYER_RED : PLAYER_BLUE);
			_selectedUnitName = "";
			_isRed = !_isRed;
			return true;
		}
	}

	Point pos = _frame->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, _frame->getContentSize().width, _frame->getContentSize().height);
	if (rect.containsPoint(pos))
	{
		_selectedUnitName = _unitName;
		return true;
	}
	return false;
}