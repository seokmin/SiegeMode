#include "pch.h"
#include "UnitState_Attack.h"
#include "AnimationManager.h"
#include "UnitState_Approach.h"
#include "Unit.h"

void UnitState_Attack::startState(Unit* unit)
{
	auto moveDirection = unit->getOwnerPlayer() == PLAYER_RED ? -1 : 1;
	unit->startAnimate("walk");
	unit->moveBy(Vec2(moveDirection, 0), 0.f);
	unit->getDebugLabel()->setString("walking!");
}

void UnitState_Attack::runState(Unit* unit, float delta)
{

}

void UnitState_Attack::endState(Unit* unit)
{
	unit->stop();
}