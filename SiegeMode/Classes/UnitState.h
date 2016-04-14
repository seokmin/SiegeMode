#pragma once

#include "Unit.h"

class UnitState : public Node
{
public:
	virtual void StartState(Unit* unit) = 0;
	virtual void RunState(Unit* unit) = 0;
	virtual void EndState(Unit* unit) = 0;
};