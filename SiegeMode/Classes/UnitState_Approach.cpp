#include "pch.h"
#include "UnitState_Approach.h"
#include "AnimationManager.h"
#include "Unit.h"
#include "UnitState_Attack.h"
#include "UnitState_WalkAndSeek.h"

void UnitState_Approach::startState(Unit* unit)
{
	unit->startAnimate("walk", true);
	// 디버그용
#if _DEBUG_LABEL
	unit->getDebugLabel()->setString("Approaching!!");
#endif
}

void UnitState_Approach::runState(Unit* unit, float delta)
{
	auto a = unit->getOwnerPlayer() == DEF::PLAYER_BLUE ? 1 : -1;
	if (unit->getAttackTarget() == nullptr// 타겟이 죽었거나 
		|| a*unit->getAttackTarget()->getPositionX() > a*unit->getPositionX()// 타겟이 나보다 뒤에 있으면
		)
	{
		// 다시 탐색
		unit->changeState<UnitState_WalkAndSeek>();
		return;
	}

	// 타겟쪽으로 매프레임 조금씩 걸어간다
	auto normalVec = (unit->getAttackTarget()->getPosition() - unit->getPosition()).getNormalized();
	normalVec *= delta * unit->getMoveSpeed();
	unit->setPosition(unit->getPosition() + normalVec);
	if (unit->getPosition().distance(unit->getAttackTarget()->getPosition()) <= unit->getAttackRange())
		unit->changeState<UnitState_Attack>();
}

void UnitState_Approach::endState(Unit* unit)
{
	unit->stopAnimation();
	unit->stopMove();
}