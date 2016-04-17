#pragma once
#include "UnitState.h"

class UnitState_Approach : public UnitState
{
public:
	CREATE_FUNC(UnitState_Approach);
	bool init() { return true; }
	void startState(Unit* unit);
	void runState(Unit* unit);
	void endState(Unit* unit);
private:
	MoveTo* _moveTo = nullptr;
};