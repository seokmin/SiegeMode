#pragma once
#include "Unit.h"

class Bowman :
	public Unit
{
public:
	bool init(PLAYER_KIND playerKind) override;
	CREATE_FUNC_UNIT(Bowman);
};