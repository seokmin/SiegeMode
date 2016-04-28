#include "pch.h"
#include "UnitState_Attack.h"
#include "AnimationManager.h"
#include "UnitState_Approach.h"
#include "Unit.h"
#include "UnitState_Walk.h"

void UnitState_Attack::startState(Unit* unit)
{

}

void UnitState_Attack::runState(Unit* unit, float delta)
{
	if (unit->getAttackTarget() == nullptr)
	{
		unit->changeState<UnitState_Walk>();
		return;
	}

	_elapsedTimeFromLastAttack += delta;

	if (_elapsedTimeFromLastAttack >= unit->getAttackSpeed())
	{
		unit->attackOnce();
		_elapsedTimeFromLastAttack = 0.0;
	}

}

void UnitState_Attack::endState(Unit* unit)
{
	unit->stop();
}