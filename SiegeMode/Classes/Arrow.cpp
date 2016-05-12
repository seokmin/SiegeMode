#include "pch.h"
#include "Arrow.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"

bool Arrow::init(PLAYER_KIND playerKind)
{
	if (!Unit::init(playerKind))
		return false;
	_attackSpeed = 1.f;
	_moveSpeed = 30.f;
	_attackRange = 450.f;
	_sightRange = 500.f;
	_attackDelay = 0.4f;
	_attackPower = 7;
	_health = 30;
	_attackAccuracy = 0.5f;

	this->setUnitName("Arrow");
	if (this->getOwnerPlayer() == PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_red", 0.1f, "SpriteSource/Arrow/Arrow_walk_red.png", 30, 28, 6);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_blue", 0.1f, "SpriteSource/Arrow/Arrow_walk_blue.png", 30, 28, 6);

	if (this->getOwnerPlayer() == PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_red", 0.2f, "SpriteSource/Arrow/Arrow_attack_red.png", 35, 28, 3);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_blue", 0.2f, "SpriteSource/Arrow/Arrow_attack_blue.png", 35, 28, 3);

	this->changeState<UnitState_WalkAndSeek>();
	return true;
}

void Arrow::attackOnce()
{
	this->setAnchorPoint(Vec2(25.f / 43.f, 5.f / 30.f));
	Unit::attackOnce();
}
void Arrow::moveTo(Vec2 destination)
{
	this->setAnchorPoint(Vec2(20.f / 32.f, 4.f / 29.f));
	Unit::moveTo(destination);
}

void Arrow::moveBy(Vec2 directionVec, float duration)
{
	this->setAnchorPoint(Vec2(20.f / 32.f, 4.f / 29.f));
	Unit::moveBy(directionVec, duration);
}