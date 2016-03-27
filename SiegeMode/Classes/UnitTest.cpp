#include "pch.h"
#include "UnitTest.h"

bool UnitTest::init()
{
	/*
	* 부모 클래스의 init()도 예의상 호출해준다.
	*/
	if (!this->Unit::init())
		return false;

	return true;
}