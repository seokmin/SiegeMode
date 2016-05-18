#pragma once
#include "Unit.h"

class Balistar :
	public Unit
{
public:
	bool	init(DEF::PLAYER_KIND playerKind) override;
	void	attackOnce() override;
	void	moveBy(Vec2 directionVec, float duration) override;
	virtual Unit *	scanTarget();
	virtual bool	isRightTarget(Unit* target);
	void	moveTo(Vec2 destination) override;
	CREATE_FUNC_UNIT(Balistar);
	void	shootArrow(Vec2 targetPos);
	CC_SYNTHESIZE(float, _arrowSpeed, ArrowSpeed);
private:
	float _arrowTime;
	float _attackRangeMin;

};