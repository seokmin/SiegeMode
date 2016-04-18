#pragma once
#include "UnitState.h"

class UnitState_Walk : public UnitState
{
public:
	CREATE_FUNC(UnitState_Walk);
	bool init() override { return true; }
	void startState(Unit* unit) override;
	void runState(Unit* unit, float delta) override;
	void endState(Unit* unit) override;
};