#pragma once

#include "UnitState.h"
#include "SimpleAudioEngine.h"

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
	ACTION_ERROR,
	ACTION_ANIMATE,
	ACTION_MOVE,
	ACTION_NOT_CALLFUNC
};

class Unit :
	public Sprite
{
public:
	virtual bool init(PLAYER_KIND playerKind);
	virtual void		update(float delta) override;
	template<typename T_STATE>
	void				changeState();


	int					_tagAttackTarget = -1;
	Unit*				getAttackTarget();
	void setAttackTarget(int targetTag);

	CC_SYNTHESIZE(UnitState*, _state, State);
	CC_SYNTHESIZE(std::string, _unitName, UnitName);
	CC_SYNTHESIZE(float, _attackRange, AttackRange);
	CC_SYNTHESIZE(float, _attackSpeed, AttackSpeed);
	CC_SYNTHESIZE(float, _moveSpeed, MoveSpeed);
	CC_SYNTHESIZE(float, _sightRange, SightRange);
	CC_SYNTHESIZE(int, _health, Health);
	CC_SYNTHESIZE(unsigned, _attackPower, AttackPower);
	CC_SYNTHESIZE_READONLY(PLAYER_KIND, _ownerPlayer, OwnerPlayer);
	CC_SYNTHESIZE(float, _attackDelay, AttackDelay);
	CC_SYNTHESIZE(bool, _isDead, IsDead);
	CC_SYNTHESIZE(float, _attackAccuracy, AttackAccuracy);

	Unit*				scanNearestTarget();
	virtual void		kill();
	virtual void		moveTo(Vec2 destination);
	virtual void		moveBy(Vec2 directionVec, float duration);
	void				stopMove();
	void				stopAnimation();
	void				startAnimate(std::string animName, bool isRepeatForever);
	virtual void		attackOnce();
	virtual void		beHit(unsigned attackPower);
	void				scheduleBeHit(unsigned attackPower, float delay);
	virtual void		onExit() override { Node::onExit(); }
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