#include "pch.h"
#include "Swordman.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"

bool Swordman::init(DEF::PLAYER_KIND playerKind)
{
	setUnitName("swordman");
	if (!Unit::init(playerKind))
		return false;
	changeState<UnitState_WalkAndSeek>();
	return true;
}

void Swordman::moveTo(Vec2 destination)
{
	setAnchorPoint(Vec2(20.f / 32.f, 4.f / 29.f));
	Unit::moveTo(destination);
}

void Swordman::moveBy(Vec2 directionVec, float duration)
{
	setAnchorPoint(Vec2(20.f / 32.f, 4.f / 29.f));
	Unit::moveBy(directionVec, duration);
}

void Swordman::attackOnce()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/stab.wav");
	setAnchorPoint(Vec2(25.f / 43.f, 5.f / 30.f));
	Unit::attackOnce();
}
