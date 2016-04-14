#include "pch.h"
#include "Unit.h"
#include "UnitState.h"

bool Unit::init()
{
	this->setScale(2.f);
	return true;
}

void Unit::tick()
{
	this->getState()->RunState(this);
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

void Unit::attack()
{

}