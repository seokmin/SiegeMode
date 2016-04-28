#include "pch.h"
#include "UnitState_Walk.h"
#include "AnimationManager.h"
#include "UnitState_Approach.h"
#include "Unit.h"

void UnitState_Walk::startState(Unit* unit)
{
	auto moveDirection = unit->getOwnerPlayer() == PLAYER_RED ? -1 : 1;
	unit->startAnimate("walk", true);
	unit->moveBy(Vec2(moveDirection, 0), 0.f);
	unit->getDebugLabel()->setString("walking!");
}

void UnitState_Walk::runState(Unit* unit, float delta)
{
	//너무멀리가면 죽음.테스트코드
	if (unit->getPositionX() < 0)
		unit->kill();
	auto nearestTarget = unit->scanNearestTarget();
	if (nearestTarget && nearestTarget->getPosition().getDistance(unit->getPosition()) <= unit->getSightRange())
	{
		unit->setAttackTarget(nearestTarget);
		unit->changeState<UnitState_Approach>();
	}
}

void UnitState_Walk::endState(Unit* unit)
{
	unit->stop();
}