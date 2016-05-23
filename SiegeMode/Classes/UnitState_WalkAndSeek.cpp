#include "pch.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"
#include "UnitState_Approach.h"
#include "Unit.h"


void UnitState_WalkAndSeek::startState(Unit* unit)
{
	// 걸을 방향이 진영에 따라 달라짐
	auto moveDirection = unit->getOwnerPlayer() == DEF::PLAYER_BLUE ? -1 : 1;

	unit->startAnimate("walk", true);
	unit->moveBy(Vec2(moveDirection, 0), 0.f);
#if _DEBUG_LABEL
	unit->getDebugLabel()->setString("walking!");
#endif
}

void UnitState_WalkAndSeek::runState(Unit* unit, float delta)
{
	// 화면 벗어나면 죽음
	if (unit->getPositionX() < 0 || unit->getPositionX() > DEF::SCREEN_WIDTH)
	{
		unit->kill();
		return;
	}

	// 적합한 타겟이 있나 검색
	auto properTarget = unit->scanTarget();
	if (properTarget)//있으면
	{
		// 타겟으로 설정
		unit->setAttackTargetByTag(properTarget->getTag());
		// 타겟을 향해 접근
		unit->changeState<UnitState_Approach>();
	}
}

void UnitState_WalkAndSeek::endState(Unit* unit)
{
	unit->stopAnimation();
	unit->stopMove();
}