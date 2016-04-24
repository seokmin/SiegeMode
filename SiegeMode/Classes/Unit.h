#pragma once

#include "UnitState.h"


//Unit 자식 클래스를 위한 CREATE_FUNC
#define CREATE_FUNC_UNIT(__TYPE__) \
static __TYPE__* create(PLAYER_KIND ownerPlayer) \
{ \
    __TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
    if (pRet && pRet->init(ownerPlayer)) \
    { \
        pRet->autorelease(); \
		pRet->scheduleUpdate();\
        return pRet; \
    } \
    else \
    { \
        delete pRet; \
        pRet = nullptr; \
        return nullptr; \
    } \
}

enum ACTION_KIND {
	ACTION_ANIMATE,
	ACTION_MOVE
};

class Unit :
	public Sprite
{
public:
	virtual bool init(PLAYER_KIND playerKind);
	CREATE_FUNC_UNIT(Unit);
	virtual void		update(float delta) override;
	template<typename T_STATE>
	void				changeState();


	CC_SYNTHESIZE(UnitState*, _state, State);
	CC_SYNTHESIZE(std::string, _unitName, UnitName);
	CC_SYNTHESIZE(float, _attackRange, AttackRange);
	CC_SYNTHESIZE(float, _attackSpeed, AttackSpeed);
	CC_SYNTHESIZE(float, _moveSpeed, MoveSpeed);
	CC_SYNTHESIZE(float, _sightRange, SightRange);
	CC_SYNTHESIZE(Unit*, _attackTarget, AttackTarget);
	CC_SYNTHESIZE(unsigned, _health, Health);
	CC_SYNTHESIZE(unsigned, _attackPower, AttackPower);
	CC_SYNTHESIZE_READONLY(PLAYER_KIND, _ownerPlayer, OwnerPlayer);
	Unit*				scanNearestTarget();
	void				kill();
	void				moveTo(Vec2 destination);
	void				moveBy(Vec2 directionVec, float duration);
	void				stop();
	void				startAnimate(std::string animName);
	void				attackOnce();
	void beHit(unsigned attackPower);
	//디버그용
	CC_SYNTHESIZE(Label*, _debugLabel, DebugLabel);
private:
};

template<typename T_STATE>
void Unit::changeState()
{
	if (_state)
	{
		this->getState()->endState(this);
		this->removeComponent(_state);
	}
	auto state = T_STATE::create();
	this->setState(state);
	this->getState()->startState(this);
	this->addComponent(state);
}
