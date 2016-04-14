#pragma once
#include "ActorComponent.h"

USING_NS_CC;

class UnitMovement :
	public ActorComponent
{
public:
	virtual bool init();

	CREATE_FUNC(UnitMovement);
};