#pragma once
#include "UnitState.h"

class UnitState_Walk : public UnitState
{
public:
	CREATE_FUNC(UnitState_Walk);
	bool init() { return true; }
	void StartState(Unit* unit);
	void RunState(Unit* unit);
	void EndState(Unit* unit);
};