#pragma once

class UnitState;

class Unit :
	public Sprite
{
public:
	bool			init();
	CREATE_FUNC(Unit);
	virtual void		update(float delta);
	void				changeState(UnitState* state);

	CC_SYNTHESIZE(UnitState*, _state, State);
	CC_SYNTHESIZE(std::string, _unitName, UnitName);
	CC_SYNTHESIZE(float, _attackRange, AttackRange);
	CC_SYNTHESIZE(float, _attackSpeed, AttackSpeed);
	CC_SYNTHESIZE(float, _moveSpeed, MoveSpeed);
	CC_SYNTHESIZE(Unit*, _attackTarget, AttackTarget);
private:
};