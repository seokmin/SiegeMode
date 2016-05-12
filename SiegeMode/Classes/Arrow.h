#pragma once
#include "Unit.h"

class Arrow :
	public Unit
{
public:
	bool	init(PLAYER_KIND playerKind) override;
	void	attackOnce() override;
	void	moveBy(Vec2 directionVec, float duration) override;
	void	moveTo(Vec2 destination) override;
	CREATE_FUNC_UNIT(Arrow);
	class Arrow : public Sprite
	{
		CREATE_FUNC(Arrow);
	};
};