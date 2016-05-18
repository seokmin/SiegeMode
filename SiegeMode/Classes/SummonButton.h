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
	CC_SYNTHESIZE(Sprite*, _unitPreview, UnitPreview);
	bool				onSprTouchBegan(Touch* touch, Event* event);
	static std::string	_selectedUnitName;
	void				onSprTouchEnd(Touch* touch, Event* event);
	bool				_isSummonAble = false;
	bool				_isSummonMode = false;
	void				onSprTouchMoved(Touch* touch, Event* event);
	void showUnitPreview(Vec2 position);
};