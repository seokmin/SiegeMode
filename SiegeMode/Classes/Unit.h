#pragma once
#include "Actor.h"
class Unit :
	public Actor
{
public:
	virtual bool init();

	bool		touchCallback(Touch* touch, Event* event);

	CREATE_FUNC(Unit);

private:
	bool		_selected = false;
	Actor*		_cursor = nullptr;
};