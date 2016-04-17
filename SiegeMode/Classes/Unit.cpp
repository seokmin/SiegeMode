#include "pch.h"
#include "Unit.h"
#include "UnitManager.h"
#include "AnimationManager.h"

bool Unit::init(PLAYER_KIND playerKind)
{
	this->Sprite::init();
	//디버그용 라벨 셋팅
#ifdef _DEBUG
	_debugLabel = Label::createWithSystemFont("","",15);
	_debugLabel->setTextColor(Color4B(255, 0, 0, 255));
	_debugLabel->setScale(1.f/2.f);
	this->addChild(_debugLabel);
#endif
	//셋팅끝


	
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
	runAction(
		Sequence::create(
			DelayTime::create(0.01f),
			CallFunc::create(
				[=]() {removeFromParentAndCleanup(true); }
			),nullptr));
}

/**

*/
void Unit::walkTo(Vec2 destination)
{
	auto animation = AnimationManager::getInstance()->getAnimation(_unitName, std::string("walk") + (_ownerPlayer == PLAYER_RED ? "_red" : "_blue"));
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));

	auto distance = destination.getDistance(this->getPosition());
	auto moveAction = MoveTo::create(/*GameSpeed*/1.f * distance / _moveSpeed, destination);
	this->runAction(moveAction);
}

void Unit::walkBy(Vec2 directionVec)
{
	directionVec = directionVec.getNormalized();

	auto animation = AnimationManager::getInstance()->getAnimation(_unitName, std::string("walk") + (_ownerPlayer == PLAYER_RED ? "_red" : "_blue"));
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));

	auto moveAction = MoveBy::create(/*GameSpeed*/1.f, directionVec * _moveSpeed);
	this->runAction(RepeatForever::create(moveAction));
}

void Unit::stop()
{
	this->stopAllActions();
}

void Unit::update(float delta)
{
	_state->runState(this);
}
