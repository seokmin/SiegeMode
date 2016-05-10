#include "pch.h"
#include "Swordman.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"

bool Swordman::init(PLAYER_KIND playerKind)
{
	if (!Unit::init(playerKind))
		return false;
	_attackSpeed = 1.f;
	_moveSpeed = 30.f;
	_attackRange = 30.f;
	_sightRange = 50.f;
	_attackDelay = 0.4f;
	_attackPower = 20;
	_health = 50;

	this->setUnitName("swordman");
	this->setTexture("SpriteSource/swordman/swordman_walk_1.png");
	if (this->getOwnerPlayer() == PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_red", 0.1f, "SpriteSource/swordman/swordman_walk_red.png", 32, 29, 6);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_blue", 0.1f, "SpriteSource/swordman/swordman_walk_blue.png", 32, 29, 6);

	if (this->getOwnerPlayer() == PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_red", 0.1f, "SpriteSource/swordman/swordman_attack_red.png", 43, 30, 6);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_blue", 0.1f, "SpriteSource/swordman/swordman_attack_blue.png", 43, 30, 6);

	this->changeState<UnitState_WalkAndSeek>();
	return true;
}