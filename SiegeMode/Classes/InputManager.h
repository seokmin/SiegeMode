#pragma once

class Actor;

class InputManager
{
public:
	static InputManager* getInstance();

	void				addTouchEvent(Actor* target);

private:
	InputManager() {};
	static InputManager*	_instance;
	void					init();
	EventDispatcher*		_dispatcher;
};