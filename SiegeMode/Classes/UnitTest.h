#pragma once
#include "Unit.h"

class UnitTest :
	public Unit
{
public:
	bool init();
	CREATE_FUNC(UnitTest);
};