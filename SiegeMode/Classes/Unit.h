#pragma once

#include "UnitState.h"
#include "SimpleAudioEngine.h"

//Unit 자식 클래스를 위한 CREATE_FUNC
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
	virtual bool		init(DEF::PLAYER_KIND playerKind);
	virtual void		update(float delta) override;
	template<typename T_STATE>
	void				changeState();


	int					_tagAttackTarget = -1;
	Unit*				getAttackTarget();
	void				setAttackTargetByTag(int targetTag);

	CC_SYNTHESIZE(UnitState*, _state, State);
	CC_SYNTHESIZE(std::string, _unitName, UnitName);
	CC_SYNTHESIZE(float, _attackRange, AttackRange);
	CC_SYNTHESIZE(float, _attackSpeed, AttackSpeed);
	CC_SYNTHESIZE(float, _moveSpeed, MoveSpeed);
	CC_SYNTHESIZE(float, _sightRange, SightRange);
	CC_SYNTHESIZE(int, _health, Health);
	CC_SYNTHESIZE(unsigned, _attackPower, AttackPower);
	CC_SYNTHESIZE_READONLY(DEF::PLAYER_KIND, _ownerPlayer, OwnerPlayer);
	CC_SYNTHESIZE(float, _attackDelay, AttackDelay);
	CC_SYNTHESIZE(bool, _isDead, IsDead);
	CC_SYNTHESIZE(float, _attackAccuracy, AttackAccuracy);

	virtual Unit*		scanTarget();
	//x에 가중치를 둔 거리를 구한다.
	float				getDistanceForRange(Vec2 range);
	Vector<Unit*>		getEnemyUnitsUnderSight();
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
	CC_SYNTHESIZE(Sprite*, _healthBar, HealthBar);
	CC_SYNTHESIZE(int, _maxHealth, MaxHealth);
	virtual void		setAnchorPoint(const Vec2& anchor) override;
private:
	//디버그용
#if _DEBUG_LABEL
	CC_SYNTHESIZE(Label*, _debugLabel, DebugLabel);
#endif
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