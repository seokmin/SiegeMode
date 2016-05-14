#include "pch.h"
#include "Swordman.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"

bool Swordman::init(DEF::PLAYER_KIND playerKind)
{
	if (!Unit::init(playerKind))
		return false;
	_attackSpeed = 1.f;
	_moveSpeed = 30.f;
	_attackRange = 40.f;
	_sightRange = 100.f;
	_attackDelay = 0.1f;
	_attackPower = 20;
	_maxHealth = 70;
	_health = _maxHealth;
	_attackAccuracy = 1.f;
	this->setUnitName("swordman");
	//this->setTexture("SpriteSource/swordman/swordman_walk_1.png");
	if (this->getOwnerPlayer() == DEF::PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_red", 0.1f, "SpriteSource/swordman/swordman_walk_red.png", 32, 29, 6);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "walk_blue", 0.1f, "SpriteSource/swordman/swordman_walk_blue.png", 32, 29, 6);

	if (this->getOwnerPlayer() == DEF::PLAYER_RED)
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_red", 0.1f, "SpriteSource/swordman/swordman_attack_red.png", 43, 30, 6);
	else
		AnimationManager::getInstance()->addAnimation(_unitName, "attack_blue", 0.1f, "SpriteSource/swordman/swordman_attack_blue.png", 43, 30, 6);

	this->changeState<UnitState_WalkAndSeek>();
	return true;
}

void Swordman::moveTo(Vec2 destination)
{
	this->setAnchorPoint(Vec2(20.f / 32.f, 4.f / 29.f));
	Unit::moveTo(destination);
}

void Swordman::moveBy(Vec2 directionVec, float duration)
{
	this->setAnchorPoint(Vec2(20.f / 32.f, 4.f / 29.f));
	Unit::moveBy(directionVec, duration);
}

void Swordman::attackOnce()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/stab.wav");
	this->setAnchorPoint(Vec2(25.f / 43.f, 5.f / 30.f));
	Unit::attackOnce();
}
