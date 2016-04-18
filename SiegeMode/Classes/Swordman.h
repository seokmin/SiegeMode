#pragma once
#include "Unit.h"

class Swordman :
	public Unit
{
public:
	bool init(PLAYER_KIND playerKind) override;
	CREATE_FUNC_UNIT(Swordman);
};