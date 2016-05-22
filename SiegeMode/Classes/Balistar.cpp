#include "pch.h"
#include "Balistar.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"
#include "UnitManager.h"

bool Balistar::init(DEF::PLAYER_KIND playerKind)
{
	this->setUnitName("balistar");
	if (!Unit::init(playerKind))
		return false;

	if (this->getOwnerPlayer() == DEF::PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_red", 0.1f, "SpriteSource/balistar/balistar_walk_red.png", 67, 51, 1);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_blue", 0.1f, "SpriteSource/balistar/balistar_walk_blue.png", 67, 51, 1);

	if (this->getOwnerPlayer() == DEF::PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_red", 0.2f, "SpriteSource/balistar/balistar_attack_red.png", 67, 51, 2);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_blue", 0.2f, "SpriteSource/balistar/balistar_attack_blue.png", 67, 51, 2);

	this->changeState<UnitState_WalkAndSeek>();
	return true;
}

void Balistar::attackOnce()
{
	this->setAnchorPoint(Vec2(29.f / 67.f, 5.f / 51.f));

	runAction(Sequence::create(
		DelayTime::create(_attackDelay), CallFuncN::create(
			CC_CALLBACK_0(Balistar::shootArrow, this, getAttackTarget()->getPosition())), nullptr));

	startAnimate("attack", false);

	_arrowTime = _position.getDistance(getAttackTarget()->getPosition()) / _arrowSpeed;
	if (RandomHelper::random_real(0.f, 1.f) <= _attackAccuracy)
		getAttackTarget()->scheduleBeHit(_attackPower, _attackDelay + _arrowTime);
}
void Balistar::moveTo(Vec2 destination)
{
	this->setAnchorPoint(Vec2(29.f / 67.f, 5.f / 51.f));
	Unit::moveTo(destination);
}

void Balistar::shootArrow(Vec2 targetPos)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/bow_release.wav");
	auto direction = _ownerPlayer == DEF::PLAYER_RED ? -1 : 1;
	targetPos += Vec2(direction * 40, 25);
	Sprite* arrow = Sprite::create("SpriteSource/balistar/balistar_arrow.png");
	auto parent = getParent()->getParent();
	parent->addChild(arrow);

	arrow->setPosition(getPosition() + Vec2(0, 60));

	arrow->getTexture()->setAliasTexParameters();
	arrow->setGlobalZOrder(DEF::ZORDER_UNIT);
	arrow->setLocalZOrder(1000);

	arrow->setRotation(360.f - (targetPos - arrow->getPosition()).getAngle() * 180.f / 3.141592f);
	arrow->setScale(1.5f);

	arrow->runAction(Sequence::create(MoveTo::create(_arrowTime, targetPos), DelayTime::create(0.05f), RemoveSelf::create(true), nullptr));

}

void Balistar::readSpecFromData()
{
	Unit::readSpecFromData();
	auto specData = UnitManager::getInstance()->getSpecData();
	auto currentUnitData = specData.get(_unitName, "failed");
	auto getData = [&currentUnitData](auto key, auto defaultVal) {return currentUnitData.get(key, defaultVal); };
	setArrowSpeed(getData("arrowSpeed", 0.f).asFloat());
	setAttackRangeMin(getData("attackRangeMin", 0.f).asFloat());
}

void Balistar::moveBy(Vec2 directionVec, float duration)
{
	this->setAnchorPoint(Vec2(29.f / 67.f, 5.f / 51.f));
	Unit::moveBy(directionVec, duration);
}

//마땅한 타겟이 없으면 nullptr 반환
//Unit클래스의 기본설정은 가장 가까운 놈을 반환
Unit* Balistar::scanTarget()
{
	auto candidates = getEnemyUnitsUnderSight();

	if (candidates.size() == 0)
		return nullptr;


	Unit* currentTarget = nullptr;
	auto maxDist = FLT_MIN;

	//나보다 뒤에있는 놈은 잘라내기 위해
	auto sign = _ownerPlayer == DEF::PLAYER_RED ? 1 : -1;
	for (auto i : candidates)
	{
		if (sign * (i->getPositionX() - getPositionX()) < 0)
			continue;
		auto tempDist = this->getDistanceForRange(i->getPosition());
		if (maxDist < tempDist)
		{
			maxDist = tempDist;
			currentTarget = i;
		}
	}

	return currentTarget;
}

bool Balistar::isRightTarget(Unit* target)
{
	auto distance = getDistanceForRange(getAttackTarget()->getPosition());
	if (distance <= getAttackRange()
		&&
		distance >= _attackRangeMin
		)	return true;
	return false;
}