#include "pch.h"
#include "SummonButton.h"
#include "UnitManager.h"

std::string SummonButton::_selectedUnitName = "";
bool SummonButton::_isRed = true;

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
	newUnit->setGlobalZOrder(DEF::ZORDER_UI);
	newFrame->setGlobalZOrder(DEF::ZORDER_UI);
	newCover->setGlobalZOrder(DEF::ZORDER_UI);
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
	return newInst;
}

void SummonButton::update(float delta)
{
	auto coolTime = _unitName == "swordman" ? 11.f : 6.f;

	if (_selectedUnitName == _unitName)
		_frame->setColor(Color3B::GREEN);
	else
		_frame->setColor(Color3B::WHITE);
	if (_frameCover->getScaleY() > 0.f)
		_frameCover->setScaleY(_frameCover->getScaleY() - delta / coolTime);
}

bool SummonButton::onSprTouchBegan(Touch* touch, Event* event)
{
	//소환체크

	if (_selectedUnitName == _unitName && _frameCover->getScaleY() <= 0.f)
	{

		Point pos = touch->getLocation();
		Rect rect = DEF::FIGHTING_ZONE;
		if (_unitName == "swordman")
			rect = Rect(rect.origin.x,rect.origin.y+50.f,(float)DEF::SCREEN_WIDTH,rect.size.height - 50);
		if (rect.containsPoint(pos))
		{
			UnitManager::getInstance()->summonUnit(_selectedUnitName, Vec2(0,pos.y), _isRed ? DEF::PLAYER_RED : DEF::PLAYER_BLUE);
			if (_unitName == "swordman")
				UnitManager::getInstance()->summonUnit(_selectedUnitName, Vec2(0, pos.y - 50), _isRed ? DEF::PLAYER_RED : DEF::PLAYER_BLUE);
			//_selectedUnitName = "";
			//_isRed = !_isRed;
			_frameCover->setScaleY(1.f);
			return true;
		}
	}

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

		return true;
	}
	return false;
}