#pragma once
#include "UnitState.h"

// 타겟에게 사정거리가 닿을 때까지 접근하는 상태
class UnitState_Approach : public UnitState
{
public:
	CREATE_FUNC(UnitState_Approach);
	bool init() override { return true; }
	void startState(Unit* unit) override;
	void runState(Unit* unit, float delta) override;
	void endState(Unit* unit) override;
};