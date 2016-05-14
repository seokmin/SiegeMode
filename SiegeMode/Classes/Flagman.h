#pragma once
#include "Unit.h"

class Flagman :
	public Unit
{
public:
	bool	init(DEF::PLAYER_KIND playerKind) override;
	CREATE_FUNC_UNIT(Flagman);
	void	kill() override;
};