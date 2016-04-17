#include "pch.h"
#include "UnitState_Approach.h"
#include "AnimationManager.h"
#include "Unit.h"

void UnitState_Approach::startState(Unit* unit)
{
	unit->getDebugLabel()->setString("Approaching!!");
	unit->walkTo(unit->getAttackTarget()->getPosition());
}

void UnitState_Approach::runState(Unit* unit)
{
	;
}

void UnitState_Approach::endState(Unit* unit)
{
	unit->stopAllActions();
}