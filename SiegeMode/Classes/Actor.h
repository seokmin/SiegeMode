#pragma once
#include <array>

class Actor : public Sprite
{
public:
	/*
	 * Node에서 선언된 init() 메소드를 재정의한다.
	 * CREATE_FUNC(PAWN)과 쌍을 이룸.
	 * create()로 생성된 후에 생성자 다음으로 호출되는 메소드이다.
	 */
	virtual bool	init();

	virtual bool	touchCallback(Touch* touch, Event* event);
	void			setSpriteFromFileName(const char* fileName);
	CREATE_FUNC(Actor);
	void			refreshStroke();
private:

	std::array<Sprite*, 8>	_strokeArray;
	const float				_strokeSize = 1.f;
};