#include "pch.h"
#include "Bowman.h"
#include "UnitState_WalkAndSeek.h"
#include "AnimationManager.h"

bool ::init(PLAYER_KIND playerKind)
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

	this->setUnitName("Bowman");
	this->setTexture("SpriteSource/Bowman/Bowman_walk_1.png");
	if (this->getOwnerPlayer() == PLAYER_RED)
	{
		AnimationManager::getInstance()->addAnimation(this->getUnitName(), "walk_red", 0.1f, 
		{
			std::string("SpriteSource/Bowman/Bowman_walk_1_red.png"),
			std::string("SpriteSource/Bowman/Bowman_walk_2_red.png"),
			std::string("SpriteSource/Bowman/Bowman_walk_3_red.png"),
			std::string("SpriteSource/Bowman/Bowman_walk_4_red.png"),
			std::string("SpriteSource/Bowman/Bowman_walk_5_red.png"),
			std::string("SpriteSource/Bowman/Bowman_walk_6_red.png") }
		);
	}
	else
	{
		AnimationManager::getInstance()->addAnimation(this->getUnitName(), "walk_blue", 0.1f,
		{
			std::string("SpriteSource/Bowman/Bowman_walk_1_blue.png"),
			std::string("SpriteSource/Bowman/Bowman_walk_2_blue.png"),
			std::string("SpriteSource/Bowman/Bowman_walk_3_blue.png"),
			std::string("SpriteSource/Bowman/Bowman_walk_4_blue.png"),
			std::string("SpriteSource/Bowman/Bowman_walk_5_blue.png"),
			std::string("SpriteSource/Bowman/Bowman_walk_6_blue.png") }
		);
	}

	if (this->getOwnerPlayer() == PLAYER_RED)
	{
		AnimationManager::getInstance()->addAnimation(this->getUnitName(), "attack_red", 0.1f,
		{
			std::string("SpriteSource/Bowman/Bowman_attack_1_red.png"),
			std::string("SpriteSource/Bowman/Bowman_attack_2_red.png"),
			std::string("SpriteSource/Bowman/Bowman_attack_3_red.png"),
			std::string("SpriteSource/Bowman/Bowman_attack_4_red.png"),
			std::string("SpriteSource/Bowman/Bowman_attack_5_red.png"), }
		);
	}
	else
	{
		AnimationManager::getInstance()->addAnimation(this->getUnitName(), "attack_blue", 0.1f,
		{
			std::string("SpriteSource/Bowman/Bowman_attack_1_blue.png"),
			std::string("SpriteSource/Bowman/Bowman_attack_2_blue.png"),
			std::string("SpriteSource/Bowman/Bowman_attack_3_blue.png"),
			std::string("SpriteSource/Bowman/Bowman_attack_4_blue.png"),
			std::string("SpriteSource/Bowman/Bowman_attack_5_blue.png"), }
		);
	}


	this->changeState<UnitState_WalkAndSeek>();
	return true;
}