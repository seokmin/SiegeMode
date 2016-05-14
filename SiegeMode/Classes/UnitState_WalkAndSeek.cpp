#include "pch.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"
#include "UnitState_Approach.h"
#include "Unit.h"
void UnitState_WalkAndSeek::startState(Unit* unit)
{
	auto moveDirection = unit->getOwnerPlayer() == DEF::PLAYER_BLUE ? -1 : 1;
	unit->startAnimate("walk", true);
	unit->moveBy(Vec2(moveDirection, 0), 0.f);
	unit->getDebugLabel()->setString("walking!");
}

void UnitState_WalkAndSeek::runState(Unit* unit, float delta)
{
	//너무멀리가면 죽음.테스트코드
	if (unit->getPositionX() < 0 || unit->getPositionX() > DEF::SCREEN_WIDTH)
	{
		unit->kill();
		return;
	}
	auto nearestTarget = unit->scanNearestTarget();
	if (nearestTarget && nearestTarget->getPosition().getDistance(unit->getPosition()) <= unit->getSightRange())
	{
		unit->setAttackTarget(nearestTarget->getTag());
		unit->changeState<UnitState_Approach>();
	}
}

void UnitState_WalkAndSeek::endState(Unit* unit)
{
	unit->stopAnimation();
	unit->stopMove();
}