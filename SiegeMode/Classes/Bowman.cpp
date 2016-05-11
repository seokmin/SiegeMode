#include "pch.h"
#include "Bowman.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"

bool Bowman::init(PLAYER_KIND playerKind)
{
	if (!Unit::init(playerKind))
		return false;
	_attackSpeed = 1.f;
	_moveSpeed = 30.f;
	_attackRange = 150.f;
	_sightRange = 200.f;
	_attackDelay = 0.4f;
	_attackPower = 20;
	_health = 50;

	this->setUnitName("bowman");
	if (this->getOwnerPlayer() == PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_red", 0.1f, "SpriteSource/bowman/bowman_walk_red.png", 30, 28, 6);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_blue", 0.1f, "SpriteSource/Bowman/bowman_walk_blue.png", 30, 28, 6);

	if (this->getOwnerPlayer() == PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_red", 0.2f, "SpriteSource/bowman/bowman_attack_red.png", 35, 28, 3);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_blue", 0.2f, "SpriteSource/bowman/bowman_attack_blue.png", 35, 28, 3);

	this->changeState<UnitState_WalkAndSeek>();
	return true;
}