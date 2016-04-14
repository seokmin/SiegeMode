#include "pch.h"
#include "Swordman.h"
#include "UnitState_Walk.h"
#include "AnimationManager.h"

bool Swordman::init()
{
	if (!Unit::init())
		return false;
	_attackSpeed = 1.f;
	_moveSpeed = 30.0;
	
	this->setUnitName("swordman");
	this->initWithFile("SpriteSource/swordman/swordman_walk_1.png");
	AnimationManager::getInstance()->addAnimation(_unitName, "walk", 0.1f,{
		"SpriteSource/swordman/swordman_walk_1.png",
		"SpriteSource/swordman/swordman_walk_2.png",
		"SpriteSource/swordman/swordman_walk_3.png",
		"SpriteSource/swordman/swordman_walk_4.png",
		"SpriteSource/swordman/swordman_walk_5.png",
		"SpriteSource/swordman/swordman_walk_6.png"});
	this->changeState(UnitState_Walk::create());
	return true;
}

void Swordman::tick()
{

}
