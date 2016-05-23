#pragma once
#include "Unit.h"

// Unit의 파생 클래스중 가장 간단한 구현.
class Swordman :
	public Unit
{
public:
	bool	init(DEF::PLAYER_KIND playerKind) override;
	void	moveTo(Vec2 destination) override;
	void	moveBy(Vec2 directionVec, float duration) override;
	void	attackOnce() override;
	CREATE_FUNC_UNIT(Swordman);
};