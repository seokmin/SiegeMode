#include "pch.h"
#include "Foot.h"

bool Foot::init()
{
	/*
	* 부모 클래스의 init()도 예의상 호출해준다.
	*/
	if (!this->Node::init())
		return false;
	return true;
}
