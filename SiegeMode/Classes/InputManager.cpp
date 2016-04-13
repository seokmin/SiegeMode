#include "pch.h"
#include "InputManager.h"
#include "Actor.h"

InputManager* InputManager::_instance = nullptr;

void InputManager::init()
{
	_dispatcher = Director::getInstance()->getEventDispatcher();
}

InputManager* InputManager::getInstance()
{
	if (!_instance)
	{
		_instance = new InputManager();
		_instance->init();
	}

	return _instance;
}