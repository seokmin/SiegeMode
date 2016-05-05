#include "pch.h"
#include "Unit.h"
#include "UnitManager.h"
#include "AnimationManager.h"

bool Unit::init(PLAYER_KIND playerKind)
{
	this->Sprite::init();
	//디버그용 라벨 셋팅
	_debugLabel = Label::createWithSystemFont("", "", 15);
	_debugLabel->setTextColor(Color4B(255, 0, 0, 255));
	_debugLabel->setScale(1.f / 2.f);
	this->addChild(_debugLabel);
	//셋팅끝

	_isDead = false;

	this->setFlippedX(playerKind == PLAYER_BLUE);
	this->_ownerPlayer = playerKind;
	this->setScale(2.f);
	return true;
}

Unit* Unit::scanNearestTarget()
{
	auto unitList = UnitManager::getInstance()->getUnitList();

	auto minDistance = FLT_MAX;
	Unit* nearestUnit = nullptr;
	for (auto i : unitList->getChildren())
	{
		if (static_cast<Unit*>(i)->getOwnerPlayer() == this->getOwnerPlayer())
			continue;
		auto distance = i->getPosition().getDistance(this->getPosition());
		if (minDistance > distance)
		{
			minDistance = distance;
			nearestUnit = static_cast<Unit*>(i);
		}
	}
	return nearestUnit;
}

void Unit::kill()
{
	// 	runAction(
	// 		Sequence::create(
	// 			DelayTime::create(0.01f),
	// 			CallFunc::create(
	// 				[=]() {removeFromParentAndCleanup(true); }
	// 	), nullptr));
	if (!_isDead)
	{
		this->unscheduleUpdate();
		removeFromParentAndCleanup(true);
		_isDead = true;
	}
}

/**

*/
void Unit::moveTo(Vec2 destination)
{
	this->stopMove();
	auto distance = destination.getDistance(this->getPosition());
	auto moveAction = MoveTo::create(/*GameSpeed*/1.f * distance / _moveSpeed, destination);
	moveAction->setTag(ACTION_MOVE);
	this->runAction(moveAction);
}

//duration에 0을 넣으면 무한반복
void Unit::moveBy(Vec2 directionVec, float duration)
{
	if (duration != 0.f)
		runAction(
			Sequence::create(
				DelayTime::create(duration + 0.01f),
				CallFunc::create(CC_CALLBACK_0(Unit::stopMove, this)), nullptr));

	directionVec = directionVec.getNormalized();

	if (duration == 0.f)
	{
		auto moveAction = RepeatForever::create(MoveBy::create(/*GameSpeed*/1.f, directionVec * _moveSpeed));
		moveAction->setTag(ACTION_MOVE);
		this->runAction(moveAction);
	}
	else
	{
		auto moveAction = MoveBy::create(/*GameSpeed*/1.f * duration, directionVec * _moveSpeed * duration);
		moveAction->setTag(ACTION_MOVE);
		this->runAction(moveAction);
	}

}

void Unit::stopMove()
{
	this->stopAllActionsByTag(ACTION_MOVE);
}

void Unit::stopAnimation()
{
	this->stopAllActionsByTag(ACTION_ANIMATE);
}

void Unit::startAnimate(std::string animName, bool isRepeatForever)
{
	this->stopAllActionsByTag(ACTION_ANIMATE);
	auto animation = AnimationManager::getInstance()->getAnimation(_unitName, animName + (_ownerPlayer == PLAYER_RED ? "_red" : "_blue"));
	Action* animate;
	if (isRepeatForever)
		animate = RepeatForever::create(Animate::create(animation));
	else
		animate = Animate::create(animation);
	animate->setTag(ACTION_ANIMATE);

	this->runAction(animate);
}

void Unit::attackOnce()
{
	startAnimate("attack", false);
	getAttackTarget()->runAction(Sequence::create(DelayTime::create(_attackDelay), CallFuncN::create(CC_CALLBACK_0(Unit::beHit, getAttackTarget(), _attackPower)), nullptr));
}

void Unit::beHit(unsigned attackPower)
{
	_health -= attackPower;
	if (_health <= 0)
		this->kill();
}

void Unit::update(float delta)
{
	_state->runState(this, delta);
}

//if failed, it will return nullptr
Unit* Unit::getAttackTarget()
{
	return UnitManager::getInstance()->getUnitByTag(_tagAttackTarget);
}

void Unit::setAttackTarget(int targetTag)
{
	if (UnitManager::getInstance()->getUnitByTag(targetTag))
		_tagAttackTarget = targetTag;
}