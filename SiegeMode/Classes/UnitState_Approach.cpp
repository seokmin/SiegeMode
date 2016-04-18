#include "pch.h"
#include "UnitState_Approach.h"
#include "AnimationManager.h"
#include "Unit.h"

void UnitState_Approach::startState(Unit* unit)
{
	unit->getDebugLabel()->setString("Approaching!!");
}

void UnitState_Approach::runState(Unit* unit, float delta)
{
	unit->walkBy(unit->getAttackTarget()->getPosition() - unit->getPosition(),delta);
}

void UnitState_Approach::endState(Unit* unit)
{
	unit->stopAllActions();
}