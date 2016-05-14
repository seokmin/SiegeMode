#pragma once

class SummonButton :
	public Node
{
public:
	static SummonButton*	create(Vec2 pos, std::string unitName);
	void					update(float delta);
private:
	CREATE_FUNC(SummonButton);
	CC_SYNTHESIZE(Sprite*, _frame, Frame);
	CC_SYNTHESIZE(Sprite*, _unit, Unit);
	CC_SYNTHESIZE(Sprite*, _frameCover, FrameCover);
	CC_SYNTHESIZE(std::string, _unitName, UnitName);
	bool				onSprTouchBegan(Touch* touch, Event* event);
	static std::string	_selectedUnitName;
	static bool			_isRed;
};