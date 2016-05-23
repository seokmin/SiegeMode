#pragma once
#include "UnitState.h"

// 그냥 가만히 있는 상태
class UnitState_Stay : public UnitState
{
public:
	CREATE_FUNC(UnitState_Stay);
	bool init() override { return true; }
	void startState(Unit* unit) override;
	void runState(Unit* unit, float delta) override;
	void endState(Unit* unit) override;
};