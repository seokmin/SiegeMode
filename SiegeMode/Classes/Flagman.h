#pragma once
#include "Unit.h"

// 승리 조건을 위해 임시로 만들어둔 유닛
// 죽으면 게임이 끝난다
class Flagman :
	public Unit
{
public:
	bool	init(DEF::PLAYER_KIND playerKind) override;
	void	kill() override;
	CREATE_FUNC_UNIT(Flagman);
};