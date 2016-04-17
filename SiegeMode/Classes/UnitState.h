#pragma once

class Unit;

class UnitState : public Component
{
public:
	virtual void startState(Unit* unit) = 0;
	virtual void runState(Unit* unit) = 0;
	virtual void endState(Unit* unit) = 0;
};