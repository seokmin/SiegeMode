#pragma once

class Actor;

class InputManager
{
public:
	static InputManager* getInstance();

	template<typename T>
	void				addTouchEvent(T* target)
	{
		auto listener = EventListenerTouchOneByOne::create();
		//listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(T::touchCallback, target);
		_dispatcher->addEventListenerWithSceneGraphPriority(listener, target);
	}

private:
	InputManager() {};
	static InputManager*	_instance;
	void					init();
	EventDispatcher*		_dispatcher;
};