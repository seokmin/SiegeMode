#pragma once
#include "UnitState.h"

class UnitState_Walk : public UnitState
{
public:
	CREATE_FUNC(UnitState_Walk);
	bool init() { return true; }
	void startState(Unit* unit);
	void runState(Unit* unit);
	void endState(Unit* unit);
};