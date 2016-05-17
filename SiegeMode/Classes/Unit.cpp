#include "pch.h"
#include "Unit.h"
#include "UnitManager.h"
#include "AnimationManager.h"

bool Unit::init(DEF::PLAYER_KIND playerKind)
{
	this->Sprite::init();
	
#if _DEBUG_LABEL
	//디버그용 라벨 셋팅
	_debugLabel = Label::createWithSystemFont("", "", 15);
	_debugLabel->setTextColor(Color4B(255, 0, 0, 255));
	_debugLabel->setScale(1.f / 2.f);
	this->addChild(_debugLabel);
	//셋팅끝
#endif
	//체력바 셋팅
	_healthBar = Sprite::create("SpriteSource/UI/healthbar.png");
	_healthBar->setOpacity(0.7 * 255);
	_healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	addChild(_healthBar);


	//셋팅끝

	_isDead = false;

	this->setFlippedX(playerKind == DEF::PLAYER_RED);
	this->_ownerPlayer = playerKind;
	this->setScale(2.f);
	return true;
}


//마땅한 타겟이 없으면 nullptr 반환
//Unit클래스의 기본설정은 가장 가까운 놈을 반환
Unit* Unit::scanTarget()
{
	auto candidates = getEnemyUnitsUnderSight();
	
	if (candidates.size() == 0)
		return nullptr;
	

	Unit* currentTarget = nullptr;
	auto minDist = FLT_MAX;
	
	//나보다 뒤에있는 놈은 잘라내기 위해
	auto sign = _ownerPlayer == DEF::PLAYER_RED ? 1 : -1;
	for (auto i : candidates)
	{
		if(sign * (i->getPositionX() - getPositionX()) < 0)
			continue;
		auto tempDist = this->getDistanceForRange(i->getPosition());
		if (minDist > tempDist)
		{
			minDist = tempDist;
			currentTarget = i;
		}
	}
	return currentTarget;
}

//단순히 range값을 반지름으로 가진 원형으로 유닛간의 거리를 검사하면 상하폭이 너무 넓다.
//상하폭을 2.5배 줄인 타원꼴로 거리를 구한다.
float Unit::getDistanceForRange(Vec2 range)
{
	auto convertedVec = this->getPosition() - range;
	convertedVec.y = convertedVec.y * 2.5;

	return convertedVec.getLength();
}

Vector<Unit*> Unit::getEnemyUnitsUnderSight()
{
	auto compareFunc = [](Unit* me, Unit* other)
	{
		if (me->getOwnerPlayer() == other->getOwnerPlayer())
			return false;
		if (me->getDistanceForRange(other->getPosition()) <= me->getSightRange())
			return true;
		return false;
	};
	auto returnVec = UnitManager::getInstance()->findUnitByCondition(
		this, compareFunc);
	return returnVec;
}
void Unit::kill()
{
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
	auto animation = AnimationManager::getInstance()->getAnimation(_unitName, animName + (_ownerPlayer == DEF::PLAYER_RED ? "_red" : "_blue"));
	Action* animate;
	if (isRepeatForever)
		animate = RepeatForever::create(Animate::create(animation));
	else
		animate = Animate::create(animation);
	animate->setTag(ACTION_ANIMATE);

	this->runAction(animate);
}

void Unit::beHit(unsigned attackPower)
{
	_health -= attackPower;
	_healthBar->setScaleX((float)_health / (float)_maxHealth);
	runAction(Sequence::create(TintTo::create(0.03f, Color3B::RED), TintTo::create(0.1f, Color3B::WHITE), nullptr));
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	if (_health <= 0)
		this->kill();
}

void Unit::scheduleBeHit(unsigned attackPower, float delay)
{
	runAction(Sequence::create(
		DelayTime::create(delay), CallFuncN::create(
			CC_CALLBACK_0(Unit::beHit, this, attackPower)
		), nullptr));
}

void Unit::setAnchorPoint(const Vec2& anchor)
{
	if (_ownerPlayer == DEF::PLAYER_BLUE)
		Sprite::setAnchorPoint(anchor);
	else
		Sprite::setAnchorPoint(Vec2(1.f - anchor.x,anchor.y));
}

void Unit::update(float delta)
{
	_healthBar->setPosition(_contentSize.width * _anchorPoint.x,0.f);
	setLocalZOrder(-_position.y);
	_state->runState(this, delta);
}

//if failed, it will return nullptr
Unit* Unit::getAttackTarget()
{
	return UnitManager::getInstance()->getUnitByTag(_tagAttackTarget);
}

void Unit::setAttackTargetByTag(int targetTag)
{
	if (UnitManager::getInstance()->getUnitByTag(targetTag))
		_tagAttackTarget = targetTag;
}

void Unit::attackOnce()
{
	startAnimate("attack", false);
	if (RandomHelper::random_real(0.f, 1.f) <= _attackAccuracy)
		getAttackTarget()->scheduleBeHit(_attackPower, _attackDelay);
}