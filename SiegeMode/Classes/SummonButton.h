#pragma once

// 유닛 소환버튼
class SummonButton :
	public Node
{
public:
	static SummonButton*	create(Vec2 pos, std::string unitName);
	void					update(float delta);
private:
	CREATE_FUNC(SummonButton);
	CC_SYNTHESIZE(Sprite*, _frame, Frame);
	CC_SYNTHESIZE(Sprite*, _unitImage, UnitImage);
	CC_SYNTHESIZE(Sprite*, _frameCover, FrameCover);
	CC_SYNTHESIZE(std::string, _unitName, UnitName);
	CC_SYNTHESIZE(Sprite*, _unitPreview, UnitPreview);
	bool				onSprTouchBegan(Touch* touch, Event* event);
	void				onSprTouchEnd(Touch* touch, Event* event);
	void				onSprTouchMoved(Touch* touch, Event* event);
	void				updateUnitPreviewColor();
	void				showOverlay();
	bool				isSummonAble();
	Vec2				_summonPoint;
	void				updateSummonPoint(Touch* touch);
	static Rect			g_summonableZone;
	static std::string	g_selectedUnitName;
};