#include "pch.h"
#include "UnitState_Walk.h"
#include "AnimationManager.h"

void UnitState_Walk::StartState(Unit* unit)
{
	auto animation = AnimationManager::getInstance()->getAnimation(unit->getUnitName(), "walk");
	auto animate = Animate::create(animation);
	unit->runAction(RepeatForever::create(animate));

	auto moveAction = MoveBy::create(1.f, Vec2(-unit->getMoveSpeed()*3, 0));
	unit->runAction(RepeatForever::create(moveAction));
}

void UnitState_Walk::RunState(Unit* unit)
{
	if (unit->getPositionX() < 10)
	{
		unit->removeFromParentAndCleanup(true);
	}
}

void UnitState_Walk::EndState(Unit* unit)
{

}