#include "pch.h"
#include "Unit.h"
#include "UnitState.h"

bool Unit::init(PLAYER_KIND playerKind)
{
	this->Sprite::init();
	this->setFlippedX(playerKind == PLAYER_BLUE);
	this->_ownerPlayer = playerKind;
	this->setScale(2.f);
	return true;
}

void Unit::changeState(UnitState* state)
{
	if (_state)
	{
		this->getState()->EndState(this);
		this->removeChild(_state,1);
	}
	this->setState(state);
	this->getState()->StartState(this);
	this->addChild(state);
}

void Unit::update(float delta)
{
	_state->RunState(this);
}
