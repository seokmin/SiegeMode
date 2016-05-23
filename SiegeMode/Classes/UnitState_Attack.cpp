#include "pch.h"
#include "UnitState_Attack.h"
#include "AnimationManager.h"
#include "UnitState_Approach.h"
#include "Unit.h"
#include "UnitState_WalkAndSeek.h"

void UnitState_Attack::startState(Unit* unit)
{
#if _DEBUG_LABEL
	unit->getDebugLabel()->setString("Attacking!!");
#endif
	if (unit->getAttackTarget() == nullptr)
	{
		unit->changeState<UnitState_WalkAndSeek>();
		return;
	}
	// 일단 한대 때리고
	unit->attackOnce();
}

void UnitState_Attack::runState(Unit* unit, float delta)
{
	_elapsedTimeFromLastAttack += delta;

	// 시간이 됐을때 때린다
	if (_elapsedTimeFromLastAttack >= unit->getAttackSpeed())
	{
		//타겟이 죽었거나, 나를 지나쳤거나, 범위를 벗어났으면 다시 걷는다.

		auto a = unit->getOwnerPlayer() == DEF::PLAYER_RED ? 1 : -1;

		if (unit->getAttackTarget() != nullptr)
		{// 타겟이 유효해야함
			if (a*(unit->getAttackTarget()->getPositionX() - unit->getPositionX()) >= 0)
			{// 타겟이 내 뒤로 가면 안됨
				if(unit->isRightTarget(unit->getAttackTarget()))
				{// 타겟이 내 공격범위 안에 들어있어야됨
					unit->attackOnce();
					_elapsedTimeFromLastAttack = 0.0;
					return;
				}
			}
		}
		// 위 조건 하나라도 만족 못하면 새로 찾아야됨
		unit->changeState<UnitState_WalkAndSeek>();
		return;
	}

}

void UnitState_Attack::endState(Unit* unit)
{
}