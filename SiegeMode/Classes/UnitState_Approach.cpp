#include "pch.h"
#include "UnitState_Approach.h"
#include "AnimationManager.h"
#include "Unit.h"

void UnitState_Approach::startState(Unit* unit)
{
	unit->startAnimate("walk");
	unit->getDebugLabel()->setString("Approaching!!");
}

void UnitState_Approach::runState(Unit* unit, float delta)
{
	auto normalVec = (unit->getAttackTarget()->getPosition() - unit->getPosition()).getNormalized();
	normalVec *= delta * unit->getMoveSpeed();
	unit->setPosition(unit->getPosition() + normalVec);
}

void UnitState_Approach::endState(Unit* unit)
{
	unit->stopAllActions();
}