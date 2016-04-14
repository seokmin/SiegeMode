#include "pch.h"
#include "UnitState_Walk.h"
#include "AnimationManager.h"

void UnitState_Walk::StartState(Unit* unit)
{
	auto animation = AnimationManager::getInstance()->getAnimation(unit->getUnitName(), "walk");
	auto animate = Animate::create(animation);
	unit->runAction(RepeatForever::create(animate));
}

void UnitState_Walk::RunState(Unit* unit)
{
	
}

void UnitState_Walk::EndState(Unit* unit)
{

}
