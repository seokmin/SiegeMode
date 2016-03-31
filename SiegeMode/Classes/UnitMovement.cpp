#include "pch.h"
#include "UnitMovement.h"

bool UnitMovement::init()
{
	/*
	* 부모 클래스의 init()도 예의상 호출해준다.
	*/
	if (!this->ActorComponent::init())
		return false;
	return true;
}