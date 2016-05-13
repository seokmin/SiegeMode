#pragma once

class SummonButton :
	public Node
{
public:
	static SummonButton* create(Vec2 pos, std::string unitName);
private:
	CREATE_FUNC(SummonButton);
	bool onSprTouchBegan(Touch* touch, Event* event);
	CC_SYNTHESIZE(Sprite*, _frame, Frame);
	CC_SYNTHESIZE(Sprite*, _unit, Unit);
	CC_SYNTHESIZE(std::string, _unitName, UnitName);
	static std::string _selectedUnitName;
	static bool _isRed;
};