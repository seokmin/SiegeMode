#pragma once
#include "ActorComponent.h"

class UnitArmor :
	public ActorComponent
{
public:
	UnitArmor();
	virtual ~UnitArmor();

	CREATE_FUNC(UnitArmor);
};