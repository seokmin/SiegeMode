#include "pch.h"
#include "UnitState_Walk.h"
#include "AnimationManager.h"

void UnitState_Walk::StartState(Unit* unit)
{
	auto animation = AnimationManager::getInstance()->getAnimation(unit->getUnitName(), std::string("walk") + (unit->getOwnerPlayer()==PLAYER_RED ? "_red" : "_blue"));
	auto animate = Animate::create(animation);
	unit->runAction(RepeatForever::create(animate));

	auto moveDirection = unit->getOwnerPlayer() == PLAYER_RED ? -1 : 1;
	auto moveAction = MoveBy::create(1.f, Vec2(moveDirection * unit->getMoveSpeed(), 0));
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