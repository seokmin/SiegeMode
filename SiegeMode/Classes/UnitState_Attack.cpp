#include "pch.h"
#include "UnitState_Attack.h"
#include "AnimationManager.h"
#include "UnitState_Approach.h"
#include "Unit.h"
#include "UnitState_WalkAndSeek.h"

void UnitState_Attack::startState(Unit* unit)
{
	unit->getDebugLabel()->setString("Attacking!!");
	if (unit->getAttackTarget() == nullptr)
	{
		unit->changeState<UnitState_WalkAndSeek>();
		return;
	}
	unit->attackOnce();
}

void UnitState_Attack::runState(Unit* unit, float delta)
{
	if (unit->getAttackTarget() == nullptr)
	{
		unit->changeState<UnitState_WalkAndSeek>();
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
	//unit->stop();
}