#include "pch.h"
#include "Unit.h"
#include "UnitManager.h"
#include "AnimationManager.h"
#include "json/json.h"

// 초기화 함수. CREATE 호출시 자동 호출.
bool Unit::init(DEF::PLAYER_KIND ownerPlayer)
{
	Sprite::init();

	// 유닛 스펙 불러오기
	readSpecFromData();

#if _DEBUG_LABEL
	//디버그용 라벨 셋팅
	_debugLabel = Label::createWithSystemFont("", "", 15);
	_debugLabel->setTextColor(Color4B(255, 0, 0, 255));
	_debugLabel->setScale(1.f / 2.f);
	addChild(_debugLabel);
	// 셋팅끝
#endif
	// 체력바 셋팅
	_healthBar = Sprite::create("SpriteSource/UI/healthbar.png");
	_healthBar->setOpacity(0.7 * 255);
	_healthBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	addChild(_healthBar);
	// 셋팅끝

	_isDead = false;

	// 레드진영은 한번 뒤집어준다. 스프라이트 방향이 같기때문.
	setFlippedX(ownerPlayer == DEF::PLAYER_RED);

	_ownerPlayer = ownerPlayer;
	
	setScale(2.f);

	return true;
}

// 시야에 들어온 적 유닛중 하나를 타겟팅한다.
// 마땅한 타겟이 없으면 nullptr 반환
// Unit클래스의 기본설정은 가장 가까운 놈을 반환
Unit* Unit::scanTarget()
{
	auto candidates = getEnemyUnitsUnderSight();
	
	// 시야에 들어온 적 유닛이 없음
	if (candidates.size() == 0)
		return nullptr;
	

	Unit* currentTarget = nullptr;
	auto minDist = FLT_MAX;
	

	auto sign = _ownerPlayer == DEF::PLAYER_RED ? 1 : -1;
	for (auto i : candidates)
	{
		// 나보다 뒤에 있는 놈은 잘라낸다.
		if(sign * (i->getPositionX() - getPositionX()) < 0)
			continue;

		auto tempDist = getDistanceForRange(i->getPosition());
		// 제일 가까운 놈을 찾는다.
		if (minDist > tempDist)
		{
			minDist = tempDist;
			currentTarget = i;
		}
	}
	return currentTarget;
}

// 단순히 range값을 반지름으로 가진 원형으로 유닛간의 거리를 검사하면 상하폭이 너무 넓다.
// x에 가중치를 둬서 상하폭을 줄인 타원꼴로 거리를 구한다.
float Unit::getDistanceForRange(Vec2 range)
{
	auto convertedVec = getPosition() - range;
	convertedVec.y = convertedVec.y * 2.5;// y거리를 늘려버려서 비중이 낮아지게 한다

	return convertedVec.getLength();
}

// 시야에 들어있는 적 유닛을 모두 찾아 반환
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

// 유닛을 죽인다.
// 객체가 즉시 파괴됨은 보장할 수 없음
void Unit::kill()
{
	if (!_isDead)
	{
		unscheduleUpdate();
		removeFromParentAndCleanup(true);
		_isDead = true;
	}
}

// destination까지 움직인다.
// 파생클래스에서 재정의해서 anchorPoint를 맞춰주어야 함
void Unit::moveTo(Vec2 destination)
{
	stopMove();
	auto distance = destination.getDistance(getPosition());
	auto moveAction = MoveTo::create(1.f * distance / _moveSpeed, destination);
	moveAction->setTag(ACTION_MOVE);
	runAction(moveAction);
}

// directionVec 방향으로 지정한 시간만큼 움직인다.
// duration에 0을 넣으면 무한반복
// directionVec은 정규화되어있지 않아도 됨
// 파생클래스에서 재정의해서 anchorPoint를 맞춰주어야 함
void Unit::moveBy(Vec2 directionVec, float duration)
{
	// 멈추기 예약
	if (duration != 0.f)
		runAction(
			Sequence::create(
				DelayTime::create(duration + 0.01f), //0.01f 지우면 안됨
				CallFunc::create(CC_CALLBACK_0(Unit::stopMove, this)), nullptr));

	// 방향벡터를 정규화
	directionVec = directionVec.getNormalized();


	if (duration == 0.f)// 무한히 걷기
	{
		auto moveAction = RepeatForever::create(MoveBy::create(1.f, directionVec * _moveSpeed));
		moveAction->setTag(ACTION_MOVE);
		runAction(moveAction);
	}
	else// 정해진 시간동안 걷기
	{
		auto moveAction = MoveBy::create(1.f * duration, directionVec * _moveSpeed * duration);
		moveAction->setTag(ACTION_MOVE);
		runAction(moveAction);
	}

}

// moveTo, moveBy 전용 함수
// 그만 걷기
void Unit::stopMove()
{
	stopAllActionsByTag(ACTION_MOVE);
}

// 실행중인 애니메이션을 중단
void Unit::stopAnimation()
{
	stopAllActionsByTag(ACTION_ANIMATE);
}

// 애니메이션 시작
void Unit::startAnimate(std::string animName, bool isRepeatForever)
{
	// 실행중이던 애니메이션 중단
	stopAnimation();
	
	auto animation = AnimationManager::getInstance()->getAnimation(_unitName, animName + (_ownerPlayer == DEF::PLAYER_RED ? "_red" : "_blue"));
	Action* animate;
	if (isRepeatForever)
		animate = RepeatForever::create(Animate::create(animation));
	else
		animate = Animate::create(animation);
	
	animate->setTag(ACTION_ANIMATE);
	runAction(animate);
}

// 유닛이 맞았을 때의 로직
// 유닛을 때리고 싶으면 이 함수를 호출하지 말고 scheduleBeHit을 호출할 것
void Unit::beHit(unsigned attackPower)
{
	_health -= attackPower;
	
	//체력바 갱신
	_healthBar->setScaleX((float)_health / (float)_maxHealth);
	
	// 맞았을 때 빨갛게 번쩍 하는 효과
	runAction(Sequence::create(TintTo::create(0.03f, Color3B::RED), TintTo::create(0.1f, Color3B::WHITE), nullptr));
	
	//맞는 소리
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/hit.wav");
	
	if (_health <= 0)
		kill();
}

// 유닛을 때리고 싶을 때 이 함수를 호출
void Unit::scheduleBeHit(unsigned attackPower, float delay)
{
	runAction(Sequence::create(
		DelayTime::create(delay), CallFuncN::create(
			CC_CALLBACK_0(Unit::beHit, this, attackPower)
		), nullptr));
}

// 유닛 진영에 따라 x축이 뒤집혀있을 수 있으므로 앵커포인트를 다르게 잡아주어야함
void Unit::setAnchorPoint(const Vec2& anchor)
{
	if (_ownerPlayer == DEF::PLAYER_BLUE)
		Sprite::setAnchorPoint(anchor);
	else
		Sprite::setAnchorPoint(Vec2(1.f - anchor.x,anchor.y));
}


// 타겟이 내 공격범위를 벗어났는지 검사
bool Unit::isRightTarget(Unit* target)
{
	if (getDistanceForRange(getAttackTarget()->getPosition()) <= getAttackRange())
		return true;
	return false;
}

// 유닛 스펙을 불러온다.
// 이하는 이 함수가 기본으로 불러오는 스펙
// attackDelay, accuracy, attackPower, attackRange, attackSpeed, maxHealth, moveSpeed, sightRange
// 위 목록 이외의 파생 클래스에서 추가적으로 정의한 스펙은 파생클래스에서 이 함수를 재정의하여 알아서 불러온다.
void Unit::readSpecFromData()
{
	auto specData = UnitManager::getInstance()->getSpecData();
	auto currentUnitData = specData.get(_unitName,"failed");
	auto getData = [&currentUnitData](auto key, auto defaultVal) {return currentUnitData.get(key, defaultVal); };
	setAttackDelay(getData("attackDelay", 0.f).asFloat());
	setAttackAccuracy(getData("accuracy", 0.f).asFloat());
	setAttackPower(getData("attackPower", 0).asInt());
	setAttackRange(getData("attackRange", 0.f).asFloat());
	setAttackSpeed(getData("attackSpeed", 0.f).asFloat());
	setMaxHealth(getData("maxHealth", 0).asInt());
	setHealth(getMaxHealth());
	setMoveSpeed(getData("moveSpeed", 0.f).asFloat());
	setSightRange(getData("sightRange", 0.f).asFloat());
}

// 매 프레임 호출
void Unit::update(float delta)
{
	// 여러 애니메이션 각각에 대해 대응하는 것보다 매프레임 잡아주는 것이 더 낫다고 판단.
	_healthBar->setPosition(_contentSize.width * _anchorPoint.x,0.f);

	// z값 갱신
	setLocalZOrder(-_position.y);
	
	// 로직코드
	_state->runState(this, delta);
}

// UnitManager에서 tag정보를 통해 attackTarget을 얻어온다.
// target에 대한 포인터를 직접 다루지 않고 tag만 들고있다.
// if failed, it will return nullptr
Unit* Unit::getAttackTarget()
{
	return UnitManager::getInstance()->getUnitByTag(_tagAttackTarget);
}
void Unit::setAttackTargetByTag(int targetTag)
{
	if (UnitManager::getInstance()->getUnitByTag(targetTag))
		_tagAttackTarget = targetTag;
}

// 타겟팅한 대상을 한 번 공격한다.
void Unit::attackOnce()
{
	startAnimate("attack", false);
	if (RandomHelper::random_real(0.f, 1.f) <= _attackAccuracy)
		getAttackTarget()->scheduleBeHit(_attackPower, _attackDelay);
}