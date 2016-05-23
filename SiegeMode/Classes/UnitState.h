#pragma once

class Unit;

// Unit의 런타임 로직을 수행할 State
class UnitState : public Component
{
public:
	// State 시작시 코드
	virtual void startState(Unit* unit) = 0;
	// 매 프레임 호출될 코드
	virtual void runState(Unit* unit, float delta) = 0;
	// State 끝날시 코드
	virtual void endState(Unit* unit) = 0;
};