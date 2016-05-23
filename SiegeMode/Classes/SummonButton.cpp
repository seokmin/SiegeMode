#include "pch.h"
#include "SummonButton.h"
#include "UnitManager.h"

std::string SummonButton::g_selectedUnitName = "";
Rect SummonButton::g_summonableZone = Rect(DEF::FIGHTING_ZONE.origin,Size(DEF::FIGHTING_ZONE.size.width/3.f,DEF::FIGHTING_ZONE.size.height));

SummonButton* SummonButton::create(Vec2 pos, std::string unitName)
{
	g_selectedUnitName = "";

	auto newInst = SummonButton::create();
	newInst->setPosition(pos);
	newInst->setGlobalZOrder(DEF::ZORDER_UI);
	newInst->setAnchorPoint(Vec2(0.f, 0.f));
	newInst->setUnitName(unitName);
	newInst->scheduleUpdate();

	// 자식 스프라이트들에 대한 일괄작업
	auto tempFactory = [=](std::string fileName, int zorder) {
		constexpr auto zOrigin = 0;
		auto tempSpr = Sprite::create(fileName);
		tempSpr->setLocalZOrder(zOrigin + zorder);
		tempSpr->getTexture()->setAliasTexParameters();
		tempSpr->setGlobalZOrder(DEF::ZORDER_UI);
		newInst->addChild(tempSpr);
		return tempSpr;
	};
	// newFrame		: 테두리 상자
	// newCover		: 쿨타임 표시할 덮개
	// newUnitImage : 해당 유닛 이미지
	// 이하는 구현이 바뀌지 않는 이상 바뀔 일이 없는 문자 리터럴들이므로 그냥 사용
	auto newFrame = tempFactory("SpriteSource/UI/unit_frame.png", 0);
	auto newCover = tempFactory("SpriteSource/UI/framecover.png", 2);
	auto newUnitImage = tempFactory("SpriteSource/UI/" + unitName + ".png", 1);
	newInst->setFrameCover(newCover);
	newInst->setFrame(newFrame);
	newInst->setUnitImage(newUnitImage);
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
	newInst->getUnitPreview()->setGlobalZOrder(DEF::ZORDER_UI);


	// 터치콜백 등록
	EventDispatcher* dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SummonButton::onSprTouchBegan, newInst);
	listener->onTouchEnded = CC_CALLBACK_2(SummonButton::onSprTouchEnd, newInst);
	listener->onTouchMoved = CC_CALLBACK_2(SummonButton::onSprTouchMoved, newInst);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, newInst);


	return newInst;
}

// 매 프레임 호출
void SummonButton::update(float delta)
{
	// 쿨타임을 어떻게 깔끔하게 바꿀 수 있을까
	static float coolTime;
	if (_unitName == "swordman")
		coolTime = 6.f;
	else if (_unitName == "bowman")
		coolTime = 8.f;
	else if (_unitName == "balistar")
		coolTime = 30.f;

	// 해당 버튼 선택여부 표시
	if (g_selectedUnitName == _unitName)
		_frame->setColor(Color3B::GREEN);
	else
		_frame->setColor(Color3B::WHITE);

	// 쿨타임이 아직 돌고 있으면 조금 줄여준다.
	if (_frameCover->getScaleY() > 0.f)
		_frameCover->setScaleY(_frameCover->getScaleY() - delta / coolTime);

	updateUnitPreviewColor();
}

// 터치를 뗀 순간 소환
void SummonButton::onSprTouchEnd(Touch* touch, Event* event)
{
	Point pos = touch->getLocation() + Vec2(0, 50);
	if (isSummonAble())
	{
		UnitManager::getInstance()->summonUnit(_unitName, pos, DEF::PLAYER_RED);
		// 쿨타임 돌기 시작
		_frameCover->setScaleY(1.f);
	}
	_unitPreview->setVisible(false);
}

// 움직이면 따라다님
void SummonButton::onSprTouchMoved(Touch* touch, Event* event)
{
	if (g_selectedUnitName != _unitName)
		return;
	updateSummonPoint(touch);
	updateUnitPreviewColor();
	_unitPreview->setVisible(true);
	_unitPreview->setPosition(_summonPoint - _position + Vec2(0, 20));
}

void SummonButton::updateUnitPreviewColor()
{
	if (isSummonAble())// 소환 가능시 초록색
		_unitPreview->setColor(Color3B::GREEN);
	else if (g_summonableZone.containsPoint(_summonPoint))// 쿨타임이면 주황색
		_unitPreview->setColor(Color3B::ORANGE);
	else// 소환불가지역이면 빨간색
		_unitPreview->setColor(Color3B::RED);

}

// 클릭 효과
void SummonButton::showOverlay()
{
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
}

// 소환 가능한지 판별
bool SummonButton::isSummonAble()
{
	if (_frameCover->getScaleY() > 0.f)// 쿨타임
		return false;
	if (!g_summonableZone.containsPoint(_summonPoint))// 소환가능한지역인지
		return false;
	if (g_selectedUnitName != _unitName)// 현재 선택된 놈이 나인지
		return false;
	return true;
}

// 소환하고싶은 포인트 갱신
void SummonButton::updateSummonPoint(Touch* touch)
{
	_summonPoint = touch->getLocation() + Vec2(0, 50);
}

// 터치 시작
bool SummonButton::onSprTouchBegan(Touch* touch, Event* event)
{

	//버튼이 클릭되었는지 확인
	Point pos = _frame->convertToNodeSpace(touch->getLocation());
	updateSummonPoint(touch);
	Rect currentFrameRect = Rect(0, 0, _frame->getContentSize().width, _frame->getContentSize().height);
	if (currentFrameRect.containsPoint(pos))
	{
		g_selectedUnitName = _unitName;
		showOverlay();
		return true;
	}
	if (!DEF::FIGHTING_ZONE.containsPoint(_summonPoint))
		return false;

	// 현재 선택된놈이 내가 맞으면 화면에 보여준다
	if (g_selectedUnitName == _unitName)
	{
		updateUnitPreviewColor();
		_unitPreview->setVisible(true);
		_unitPreview->setPosition(_summonPoint - _position + Vec2(0,20));
		return true;
	}
	return false;
}