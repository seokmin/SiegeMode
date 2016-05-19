#include "pch.h"
#include "SummonButton.h"
#include "UnitManager.h"

std::string SummonButton::_selectedUnitName = "";

SummonButton* SummonButton::create(Vec2 pos, std::string unitName)
{
	auto newInst = SummonButton::create();
	newInst->setPosition(pos);
	newInst->setGlobalZOrder(DEF::ZORDER_UI);

	auto newFrame = Sprite::create("SpriteSource/UI/unit_frame.png");
	auto newUnit = Sprite::create("SpriteSource/UI/" + unitName + ".png");
	auto newCover = Sprite::create("SpriteSource/UI/framecover.png");

	newCover->setLocalZOrder(newFrame->getLocalZOrder() + 2);
	newUnit->setLocalZOrder(newFrame->getLocalZOrder() + 1);
	// 	newUnit->setGlobalZOrder(DEF::ZORDER_UI);
	// 	newFrame->setGlobalZOrder(DEF::ZORDER_UI);
	// 	newCover->setGlobalZOrder(DEF::ZORDER_UI);
	newInst->addChild(newFrame);
	newInst->addChild(newUnit);
	newInst->addChild(newCover);
	newFrame->getTexture()->setAliasTexParameters();
	newUnit->getTexture()->setAliasTexParameters();
	newCover->getTexture()->setAliasTexParameters();

	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SummonButton::onSprTouchBegan, newInst);
	listener->onTouchEnded = CC_CALLBACK_2(SummonButton::onSprTouchEnd, newInst);
	listener->onTouchMoved = CC_CALLBACK_2(SummonButton::onSprTouchMoved, newInst);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, newInst);

	newInst->setFrameCover(newCover);
	newInst->setFrame(newFrame);
	newInst->setUnit(newUnit);
	newInst->setAnchorPoint(Vec2(0.f, 0.f));
	newInst->setUnitName(unitName);
	newInst->scheduleUpdate();

	newCover->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	newCover->setPositionY(newFrame->getContentSize().height / -2.f);
	newCover->setOpacity(255 * 0.7f);
	newCover->setScaleY(0.f);

	auto path = "SpriteSource/UI/" + unitName + "_preview.png";
	newInst->setUnitPreview(Sprite::create(path));
	newInst->getUnitPreview()->setVisible(false);
	newInst->getUnitPreview()->getTexture()->setAliasTexParameters();
	newInst->addChild(newInst->getUnitPreview());
	newInst->getUnitPreview()->setFlippedX(true);
	return newInst;
}

void SummonButton::update(float delta)
{
	static float coolTime;
	if (_unitName == "swordman")
		coolTime = 6.f;
	else if (_unitName == "bowman")
		coolTime = 8.f;
	else if (_unitName == "balistar")
		coolTime = 30.f;

	if (_selectedUnitName == _unitName)
		_frame->setColor(Color3B::GREEN);
	else
		_frame->setColor(Color3B::WHITE);
	if (_frameCover->getScaleY() > 0.f)
		_frameCover->setScaleY(_frameCover->getScaleY() - delta / coolTime);
}

void SummonButton::onSprTouchEnd(Touch* touch, Event* event)
{
	Point pos = touch->getLocation() + Vec2(0, 50);
	if (_isSummonAble == true)
	{
		UnitManager::getInstance()->summonUnit(_unitName, pos, DEF::PLAYER_RED);
		_frameCover->setScaleY(1.f);
	}
	_isSummonAble = false;
	_isSummonMode = false;
	_unitPreview->setVisible(false);
}



void SummonButton::onSprTouchMoved(Touch* touch, Event* event)
{
	if (_isSummonMode == false)
		return;
	auto pos = touch->getLocation() + Vec2(0, 50);
	Rect rect = DEF::FIGHTING_ZONE;
	rect.size.width = DEF::SCREEN_WIDTH / 3.f;
	if (rect.containsPoint(pos))
		_isSummonAble = true;
	else
		_isSummonAble = false;
	_unitPreview->setPosition(pos - _position + Vec2(0, 20));
	showUnitPreview(pos);
}

void SummonButton::showUnitPreview(Vec2 position)
{
	if (_isSummonAble == true)
		_unitPreview->setColor(Color3B::GREEN);
	else
		_unitPreview->setColor(Color3B::RED);

}

bool SummonButton::onSprTouchBegan(Touch* touch, Event* event)
{
	if (_frameCover->getScaleY() > 0.f)
		return false;

	Point pos = _frame->convertToNodeSpace(touch->getLocation());
	Rect rect = Rect(0, 0, _frame->getContentSize().width, _frame->getContentSize().height);
	if (rect.containsPoint(pos))
	{
		_selectedUnitName = _unitName;
		// ------- 통통 튀는 효과 ------
		runAction(
			EaseElasticOut::create(
				Sequence::create(
					ScaleTo::create(0.3f, 1.05f),
					ScaleTo::create(0.4f, 1.00f),
					nullptr)));

		// ------ 오버레이 효과 ------
		auto overlay = Sprite::createWithTexture(_frame->getTexture());

		// 밝게 빛나는 효과를 주기 위해 블렌딩을 설정한다.
		BlendFunc add;
		add.dst = GL_ONE;
		add.src = GL_SRC_ALPHA;
		overlay->setBlendFunc(add);

		overlay->runAction(
			Sequence::create(
				ScaleTo::create(0.4f, getScale() * 1.2f), RemoveSelf::create(true), nullptr));
		overlay->runAction(
			FadeOut::create(0.4f));
		overlay->setPosition(getPosition());

		getParent()->addChild(overlay);
		_unitPreview->setVisible(true);
		pos = touch->getLocation() + Vec2(0, 50);
		_unitPreview->setPosition(pos);
		_isSummonMode = true;
		return true;
	}

	//소환체크
	pos = touch->getLocation() + Vec2(0, 50);
	if (_selectedUnitName == _unitName && _frameCover->getScaleY() <= 0.f)
	{
		Rect rect = DEF::FIGHTING_ZONE;

		if (rect.containsPoint(pos))
		{
			_unitPreview->setVisible(true);
			_unitPreview->setPosition(pos);
			rect.size.width = DEF::SCREEN_WIDTH / 3.f;
			if (rect.containsPoint(pos))
				_isSummonAble = true;
			_isSummonMode = true;
			return true;
		}
	}


	return false;
}