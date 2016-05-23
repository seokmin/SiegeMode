#pragma once

#include "UnitState.h"
#include "SimpleAudioEngine.h"

// Unit 자식 클래스를 위한 CREATE_FUNC
#define CREATE_FUNC_UNIT(__TYPE__) \
static __TYPE__* create(DEF::PLAYER_KIND ownerPlayer) \
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

// 내부함수에서 쓰이기 위한 enum
enum ACTION_KIND {
	ACTION_ERROR,
	ACTION_ANIMATE,
	ACTION_MOVE,
	ACTION_NOT_CALLFUNC
};

class Unit : public Sprite
{
public:
	virtual bool				init(DEF::PLAYER_KIND playerKind);

	virtual void				update(float delta) override;

	template<typename T_STATE>
	void						changeState();
	virtual Unit*				scanTarget();
	virtual float				getDistanceForRange(Vec2 range);
	virtual Vector<Unit*>		getEnemyUnitsUnderSight();
	virtual void				kill();
	virtual void				moveTo(Vec2 destination);
	virtual void				moveBy(Vec2 directionVec, float duration);
	void						stopMove();
	void						stopAnimation();
	void						startAnimate(std::string animName, bool isRepeatForever);
	virtual void				attackOnce();
	virtual void				scheduleBeHit(unsigned attackPower, float delay);
	virtual void				onExit() override { Node::onExit(); }
	virtual void				setAnchorPoint(const Vec2& anchor) override;
	virtual bool				isRightTarget(Unit* target);

	Unit*						getAttackTarget();
	void						setAttackTargetByTag(int targetTag);
	int							_tagAttackTarget = -1;

	std::string					_unitName;
	void						setUnitName(std::string var) { _unitName = var; setName(var); }
	std::string					getUnitName() { return _unitName; }


	CC_SYNTHESIZE(UnitState*, _state, State);
	CC_SYNTHESIZE(float, _attackRange, AttackRange);
	CC_SYNTHESIZE(float, _attackSpeed, AttackSpeed);
	CC_SYNTHESIZE(float, _moveSpeed, MoveSpeed);
	CC_SYNTHESIZE(float, _sightRange, SightRange);
	CC_SYNTHESIZE(int, _health, Health);
	CC_SYNTHESIZE(unsigned, _attackPower, AttackPower);
	CC_SYNTHESIZE(float, _attackDelay, AttackDelay);
	CC_SYNTHESIZE(bool, _isDead, IsDead);
	CC_SYNTHESIZE(float, _attackAccuracy, AttackAccuracy);
	CC_SYNTHESIZE(Sprite*, _healthBar, HealthBar);
	CC_SYNTHESIZE(int, _maxHealth, MaxHealth);
	CC_SYNTHESIZE_READONLY(DEF::PLAYER_KIND, _ownerPlayer, OwnerPlayer);

protected:
	virtual void				readSpecFromData();
private:
	virtual void				beHit(unsigned attackPower);
	//디버그용
#if _DEBUG_LABEL
	CC_SYNTHESIZE(Label*, _debugLabel, DebugLabel);
#endif
};

// 유닛 상태를 전환
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