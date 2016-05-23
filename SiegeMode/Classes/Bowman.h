#pragma once
#include "Unit.h"

// ±Ã¼ö
class Bowman :
	public Unit
{
public:
	bool			init(DEF::PLAYER_KIND playerKind) override;
	void			attackOnce() override;
	void			moveBy(Vec2 directionVec, float duration) override;
	void			moveTo(Vec2 destination) override;
	void			shootArrow(Vec2 targetPos);
	CC_SYNTHESIZE(float, _arrowSpeed, ArrowSpeed);
	CREATE_FUNC_UNIT(Bowman);
protected:
	virtual void	readSpecFromData() override;
private:
	float			_arrowTime;

};