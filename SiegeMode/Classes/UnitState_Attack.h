#pragma once
#include "UnitState.h"

// 전투모드
class UnitState_Attack : public UnitState
{
public:
	CREATE_FUNC(UnitState_Attack);
	bool init() override { return true; }
	void startState(Unit* unit) override;
	void runState(Unit* unit, float delta) override;
	void endState(Unit* unit) override;
private:
	double	_elapsedTimeFromLastAttack = 0.0;
};