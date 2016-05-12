#pragma once
#include "Unit.h"

class Bowman :
	public Unit
{
public:
	bool	init(PLAYER_KIND playerKind) override;
	void	attackOnce() override;
	void	moveBy(Vec2 directionVec, float duration) override;
	void	moveTo(Vec2 destination) override;
	CREATE_FUNC_UNIT(Bowman);
	void shootArrow(Vec2 targetPos);
	CC_SYNTHESIZE(float, _arrowSpeed, ArrowSpeed);
private:
	float _arrowTime;

};