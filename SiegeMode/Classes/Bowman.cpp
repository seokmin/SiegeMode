#include "pch.h"
#include "Bowman.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"
#include "UnitManager.h"

bool Bowman::init(DEF::PLAYER_KIND playerKind)
{
	setUnitName("bowman");
	if (!Unit::init(playerKind))
		return false;

	changeState<UnitState_WalkAndSeek>();
	return true;
}

// 원래의 attackOnce는 근거리용이므로 원거리용으로 새로 작성
// 복붙 수준이고, 추후 코드 개선방법 생각중
void Bowman::attackOnce()
{
	setAnchorPoint(Vec2(25.f / 43.f, 5.f / 30.f));

	runAction(Sequence::create(
		DelayTime::create(_attackDelay), CallFuncN::create(
			CC_CALLBACK_0(Bowman::shootArrow, this, getAttackTarget()->getPosition())), nullptr));

	startAnimate("attack", false);

	_arrowTime = _position.getDistance(getAttackTarget()->getPosition()) / _arrowSpeed;
	if (RandomHelper::random_real(0.f, 1.f) <= _attackAccuracy)
		getAttackTarget()->scheduleBeHit(_attackPower, _attackDelay + _arrowTime);
}

void Bowman::moveTo(Vec2 destination)
{
	setAnchorPoint(Vec2(14.f / 30.f, 3.f / 30.f));
	Unit::moveTo(destination);
}

// 화살 한 발을 쏜다
void Bowman::shootArrow(Vec2 targetPos)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/bow_release.wav");
	auto direction = _ownerPlayer == DEF::PLAYER_RED ? -1 : 1;

	// 맞는 느낌을 위해서 상수로 맞춘다
	targetPos += Vec2(direction * 10, 25);


	Sprite* arrow = Sprite::create("SpriteSource/bowman/bowman_arrow.png");
	auto parent = getParent()->getParent();
	parent->addChild(arrow);// 화면에 addchild해야 유닛이 죽어도 화살이 남음
	
	// 쏘는 느낌을 위해서 상수로 맞춘다
	arrow->setPosition(getPosition() + Vec2(0, 20));

	arrow->getTexture()->setAliasTexParameters();
	arrow->setGlobalZOrder(DEF::ZORDER_UNIT);
	arrow->setLocalZOrder(1000);

	arrow->setRotation(360.f - (targetPos - _position).getAngle() * 180.f / 3.141592f);
	arrow->setScale(1.5f);

	arrow->runAction(Sequence::create(MoveTo::create(_arrowTime, targetPos), DelayTime::create(0.05f), RemoveSelf::create(true), nullptr));

}

// Bowman에서 추가로 정의한 스펙을 뽑아온다
void Bowman::readSpecFromData()
{
	Unit::readSpecFromData();
	auto specData = UnitManager::getInstance()->getSpecData();
	auto currentUnitData = specData.get(_unitName, "failed");
	auto getData = [&currentUnitData](auto key, auto defaultVal) {return currentUnitData.get(key, defaultVal); };
	setArrowSpeed(getData("arrowSpeed", 0.f).asFloat());
}

void Bowman::moveBy(Vec2 directionVec, float duration)
{
	setAnchorPoint(Vec2(14.f / 30.f, 3.f / 30.f));
	Unit::moveBy(directionVec, duration);
}